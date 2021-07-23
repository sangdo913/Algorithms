fn test(string: &mut String)-> &mut String {
    string
}

fn change(some_string: &mut String) {
    some_string.push_str(", world");
    println!("{}", some_string);
}

fn owner(some_string: &mut String){
}

fn find_str(string: &String)-> &str {
    let bytes = string.as_bytes();
    for (i, &iter) in bytes.iter().enumerate() {            
        if iter == b' ' {
            return &string[..i];
        }
    }
    return &string[..];
}

fn main() {
    let s = String::from("test and hoho");
    println!("{}", find_str(&s));
}
