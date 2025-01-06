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
}
