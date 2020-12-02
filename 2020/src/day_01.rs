use std::usize;
use std::env;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_input() -> Vec<usize> {
    let args: Vec<String> = env::args().collect();
    let input = File::open(&args[1]).expect("Cannot open file");
    let input = BufReader::new(input);

    return input.lines()
        .filter_map(|result| result.ok())
        .filter_map(|s| s.parse::<usize>().ok())
        .collect::<Vec<usize>>();
}

pub fn a() {
    let input = read_input();
    for a in &input {
        for b in &input {
            if a + b == 2020 {
                println!("Answer to 01.A: {}", a * b);
                return;
            }
        }
    }
}

pub fn b() {
    let input = read_input();
    for a in &input {
        for b in &input {
            for c in &input {
                if a + b + c == 2020 {
                    println!("Answer to 01.B: {}", a * b * c);
                    return;
                }
            }
        }
    }
}


