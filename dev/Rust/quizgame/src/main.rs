use std::{
    env,
    io::{self, stdin, Write},
    process::exit
};

fn show_usage() {
    println!("Usage: cargo run");
}

fn show_welcome_message() {
    println!("Hey whats your name?");
    print!("> ");
    let _ = io::stdout().flush();
}

fn get_answer(correct_choice: &str) -> bool {
    let _ = io::stdout().flush();
    let mut answer = String::new();
    let _ = stdin().read_line(&mut answer);
    if answer.trim().eq_ignore_ascii_case(correct_choice) {
        println!("Correct!");
        true
    }
    else {
        println!("Wrong!");
        false
    }
}

fn show_question_1() {
    println!("1. What is the capital city of France?");
    println!("A. London");
    println!("B. Paris");
    println!("C: Rome");
    print!("Your answer: ");
    let _ = io::stdout().flush();
}

fn show_question_2() {
    println!("\n2. What is the largest country in the world by area?");
    println!("A. Russia");
    println!("B. Canada");
    println!("C: China");
    print!("Your answer: ");
    let _ = io::stdout().flush();
}

fn show_question_3() {
    println!("\n3. Who is credited with inventing the World Wide Web?");
    println!("A. Bill Gates");
    println!("B. Tim Berners-Lee");
    println!("C. Steve Jobs");
    print!("Your answer: ");
    let _ = io::stdout().flush();
}


fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 1 {
        println!("Wrong numbers of arguments given");
        show_usage();
        exit(1);
    }
    
    let total_answers = 3;
    let mut correct_answers = 0;

    show_welcome_message();
    let mut user_name = String::new();
    let _ = stdin().read_line(&mut user_name);
    if user_name.trim().len() == 0 {
        println!("[!] No data entered, please enter a user name");
        exit(1);
    }
    else {
        println!("Welcome to the game {}", user_name.trim());
    }

    show_question_1();
    if get_answer("B") {
        correct_answers += 1;
    }

    show_question_2();
    if get_answer("A") {
        correct_answers += 1;
    }

    show_question_3();
    if get_answer("B") {
        correct_answers += 1;
    }

    let percentage = (correct_answers as f32 / total_answers as f32) * 100.0;
    println!("Your score: {:.2}%", percentage);

}
