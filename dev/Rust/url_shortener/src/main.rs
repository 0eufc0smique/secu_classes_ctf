use std::{
    env,
    fs::{File, OpenOptions},
    io::{self, stdin, BufRead, BufReader, Write},
    process::exit
};

use rand::{
    self,
    distributions::Alphanumeric,
    thread_rng,
    Rng
};

const URL_LENGTH: usize = 8;


fn show_usage() {
    println!("Usage: cargo run <www.example.com> <urls_file.txt>");
}


fn main() {
    let args: Vec<String> = env::args().collect();
    
    if args.len() != 3 {
        println!("Wrong numbers of arguments given.");
        show_usage();
        exit(1);
    }
    
    let url_passed = &args[1];
    let urls_path = &args[2];
    
    // open file, if doesnt exist, offer user the possibility to create it
    let mut urls_file = match OpenOptions::new().append(true).open(urls_path) {
        Ok(file) => file,
        Err(_) => {
            println!("Error opening the file: file doesn't exist");
            print!("Do you want to create the file? (yY) or (nN) > ");
            
            let _ = io::stdout().flush();
            let mut input = String::new();
            let _ = stdin().read_line(&mut input);
            
            if input.trim_end().eq_ignore_ascii_case("y") {
                let urls_file = File::create(urls_path).expect("Failed to create file");
                println!("File created at {}", urls_path);
                urls_file
            }
            else if input.trim_end().eq_ignore_ascii_case("n") {
                println!("Ok, exiting");
                exit(1);
            }
            else {
                println!("Wrong choice, exiting");
                exit(1);
            }
        } 
    };

    // shorten URL if long
    if url_passed.starts_with("www") {
        let short_url: String = thread_rng()
            .sample_iter(&Alphanumeric)
            .take(URL_LENGTH)
            .map(char::from)
            .collect();
        println!("'{}' shortened into '{}'", short_url, url_passed);
    
        // map urls and write them into mapping file
        let mapped_urls = format!("{},{}", short_url, url_passed);
        write!(urls_file, "{}\n", mapped_urls).expect("Failed to write to file");
    } 

    else if url_passed.len() != URL_LENGTH {
        println!("Please enter valid Url");
        show_usage();
        exit(1);
    }

    // if short url is given
    else {
        let mut found_match = false;

        let urls_file = match File::open(urls_path) {
            Ok(file) => file,
            Err(_) => {
                println!("Error reading the urls file");
                return;
            }
        };
        
        // if file could be opened, create a reader to parse lines
        let reader = BufReader::new(urls_file);
        for line in reader.lines() {
            let mapping = match line {
                Ok(line) => line,
                Err(_) => {
                    println!("Error reading mapping file");
                    continue; 
                }
            };

            // create iterable vector which stores lines content 
            let parts: Vec<&str> = mapping.split(',').collect();
            
            // if not two urls, dont care
            if parts.len() != 2{
                continue;
            }
            // if two urls, look for match
            else {
                let short_url = parts[0];
                let long_url = parts[1];
                if url_passed == short_url {
                    println!("[*] Match: {} gives: {}", url_passed, long_url);
                    found_match = true;
                }
                else {
                    continue;
                }
            }
        }

        if !found_match {
            println!("[!] No match found for: {}", url_passed);
        }
    }
}


/* 
Concepts used:
When taking user input:
- The standard output (stdout) stream is line-buffered, which means text isn't usually flushed to the console until a newline appears.  
Since we want the > character to appear without printing a new line, we have to manually flush stdout so that it appears.
- We used "trim_end() on user input to remove the new line char added (its a string, it ends with a newline)"
*/
