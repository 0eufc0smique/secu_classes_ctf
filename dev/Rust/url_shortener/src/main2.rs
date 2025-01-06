use std::{
    env,
    fs::{File, OpenOptions},         // file operations
    io::{BufRead, BufReader, Write}, // reading and writing files
};

use rand::{distributions::Alphanumeric, Rng}; // random string


fn main() {
    // Define the path to the file that stores URL mappings
    let mapping_path = "src/mapping.txt";

    // Collect command-line arguments into a vector
    let args: Vec<String> = env::args().collect();

    // Ensure exactly one argument (the URL) is provided
    if args.len() != 2 {
        println!("Usage: ./url_shortener <url>");
        return;
    }

    // Get the URL from the command-line arguments
    let url = &args[1];

    // Check if the URL starts with "http" (indicating a long URL)
    if url.starts_with("http") {
        // **Converting a long URL to a short URL**

        // Create a random number generator
        let mut rng = rand::thread_rng();

        // Generate an 8-character random alphanumeric string
        let short_url: String = std::iter::repeat(())
            .map(|()| rng.sample(Alphanumeric) as char) // Generate random character
            .take(8) // Take 8 characters
            .collect(); // Collect into a String

        // Display the original and shortened URLs
        println!("Long URL: {}", url);
        println!("Short URL: {}", short_url);

        // Open the mapping file in append mode to add the new mapping
        let mut mapping_file = match OpenOptions::new()
            .write(true)
            .append(true)
            .open(mapping_path)
        {
            Ok(file) => file, // Successfully opened the file
            Err(_) => {
                println!("Error opening mapping file");
                return; // Exit if the file can't be opened
            }
        };

        // Create a mapping string in the format "short_url,long_url\n"
        let mapping = format!("{},{}\n", short_url, url);

        // Write the mapping to the file
        if let Err(_) = mapping_file.write_all(mapping.as_bytes()) {
            println!("Error writing to mapping file");
            return; // Exit if writing fails
        }
    } else {
        // **Redirecting from a short URL to the long URL**

        // Open the mapping file for reading
        let mapping_file = match File::open(mapping_path) {
            Ok(file) => file, // Successfully opened the file
            Err(_) => {
                println!("Error opening mapping file");
                return; // Exit if the file can't be opened
            }
        };

        // Create a buffered reader to read the file line by line
        let reader = BufReader::new(mapping_file);

        // Iterate over each line in the mapping file
        for line in reader.lines() {
            // Handle any errors in reading a line
            let mapping = match line {
                Ok(line) => line, // Successfully read a line
                Err(_) => {
                    println!("Error reading mapping file");
                    continue; // Skip to the next line on error
                }
            };

            // Split the line into short and long URLs using the comma separator
            let parts: Vec<&str> = mapping.split(',').collect();

            // Ensure the line has exactly two parts
            if parts.len() != 2 {
                continue; // Skip invalid lines
            }

            // Extract the short URL and long URL from the parts
            let short = parts[0];
            let long = parts[1];

            // Check if the short URL matches the input URL
            if short == url {
                // Found a matching short URL
                println!("Redirecting to {}", long);
                return; // Exit after finding the match
            }
        }

        // No matching short URL was found
        println!("Short URL not found");
    }
}

