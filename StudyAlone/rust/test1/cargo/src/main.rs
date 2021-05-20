use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    let secret_number = rand::thread_rng().gen_range(1,101);
    println!("let's this about the correct number!");
    println!("input number that you think correct!");

    loop {
        let mut guess = String::new();

        io::stdin().read_line(&mut guess)
            .expect("can't read input");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        println!("input: {}", guess);

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("less"),
            Ordering::Greater => println!("greater"),
            Ordering::Equal => {
                println!("correct!");
                break;
            }
        }
    }
}