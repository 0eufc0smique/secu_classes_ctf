use std::{
    env,
    fs::File,
    io::{self, BufRead},
    path::Path,
    process::exit,
};
use sha2::{Digest, Sha256};


fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}


fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 3 {
        println!("Wrong number of arguments given !");
        println!("Usage: cargo run <hashed password> <password file>");
        exit(1);
    }

    let wanted_hash = &args[1];
    let password_file = &args[2];

    if let Ok(password_list) = read_lines(password_file) {
        for (attempt, password) in password_list.flatten().enumerate() {
            let password = password.trim();
            let password_hash = format!("{:x}", Sha256::digest(&password));

            if password_hash == *wanted_hash {
                println!("hash cracked at attempt {} || hash: {} || password: {:?}", attempt + 1, wanted_hash, password);
            };
        }
    } else {
        println!("Failed to open password file");
        exit(1);
    }
}




/* //Nicolas script 
use std::{
    env,
    fs::File,
    io::{self, BufRead},
    path::Path,
    process::exit,
};
use sha2::{Digest, Sha256};


fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>> 
where P: AsRef<Path>, 
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}


fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = env::args().collect();

    if args.len() != 3 {
        println!("Wrong number of arguments given !");
        println!("Usage: cargo run <hashed password> <password file>");
        exit(1);
    }

    let wanted_hash = &args[1];
    let password_file = &args[2];

    let password_list = read_lines(password_file)?;
    let result = password_list
        .map_while(Result::ok)
        .enumerate()
        .find_map(|(i, password)| {
            let password_hash = format!("{:x}", Sha256::digest(password.trim()));
            if password_hash == *wanted_hash {
                Some((i, password_hash))
            } else {
                None
            }
        });
    if let Some((attempt, password)) = result {
        println!(
            "hash cracked at attempt: {attempt} || hash: {wanted_hash} || password: {password:?}",
        );
    }
    Ok(())
} */





/* 
HEATH SCRIPT 

use std::env;
use std::fs::File;
use std::io::{BufRead, BufReader};
use sha2::{Sha256, Digest};
use std::process::exit;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 {
        println!("Invalid arguments!");
        println!(">> {} <sha256sum>", args[0]);
        exit(1);
    }

    let wanted_hash = &args[1];
    let password_file = "src/rockyou.txt";
    let mut attempts = 1;

    println!("Attempting to hack: {}!\n", wanted_hash);

    let password_list = File::open(password_file).unwrap();
    let reader = BufReader::new(password_list);

    for line in reader.lines() {
        let line = line.unwrap();
        let password = line.trim().to_owned().into_bytes();
        let password_hash = format!("{:x}", Sha256::digest(&password));
        println!("[{}] {} == {}", attempts, std::str::from_utf8(&password).unwrap(), password_hash);
        if &password_hash == wanted_hash {
            println!("Password hash found after {} attempts! {} hashes to {}!", attempts, std::str::from_utf8(&password).unwrap(), password_hash);
            exit(0);
        }
        attempts += 1;
    }

    println!("Password hash not found!");
} */