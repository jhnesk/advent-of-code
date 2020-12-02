use std::env;
use std::fs::File;
use std::io::{BufReader};

mod day_01;
mod day_02;

fn main() {
    let args: Vec<String> = env::args().collect();

    match args[1].parse() {
        Ok(1) => {
            day_01::a(read_input("input/01.txt"));
            day_01::b(read_input("input/01.txt"));
        },
        Ok(2) => {
            day_02::a(read_input("input/02.txt"));
            day_02::b(read_input("input/02.txt"));
        },
        _ => panic!()
    }
}

fn read_input(file: &str) -> BufReader<File> {
    let input = File::open(file).expect("Cannot open file");
    return BufReader::new(input);
}
