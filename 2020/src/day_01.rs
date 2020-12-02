use std::usize;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn parse(input: BufReader<File>) -> Vec<usize> {
    return input.lines()
        .filter_map(|result| result.ok())
        .filter_map(|s| s.parse::<usize>().ok())
        .collect::<Vec<usize>>();
}

pub fn a(input: BufReader<File>) {
    let input = parse(input);
    for a in &input {
        for b in &input {
            if a + b == 2020 {
                println!("Answer to 01.A: {}", a * b);
                return;
            }
        }
    }
}

pub fn b(input: BufReader<File>) {
    let input = parse(input);
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

