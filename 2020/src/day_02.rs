extern crate scanner_rust;

use std::usize;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::str::FromStr;
use std::iter::Iterator;
use scanner_rust::ScannerStr;

struct Policy {
    min: usize,
    max: usize,
    token: char,
    password: String,
}

struct ParseError;

impl FromStr for Policy {
    type Err = ParseError;

    fn from_str(input: &str) -> Result<Self, Self::Err> {
        let mut sc = ScannerStr::new(input);

        let min: usize = sc.next_until("-").unwrap().unwrap().parse::<usize>().ok().unwrap();
        let max: usize = sc.next_usize().unwrap().unwrap();
        sc.skip_whitespaces().unwrap();
        let token: char = sc.next_char().unwrap().unwrap();
        sc.next_char().unwrap();
        sc.next_char().unwrap();
        let password: String = sc.next().unwrap().unwrap().to_string();

        Ok(Policy { min, max, token, password })
    }
}

fn parse(input: BufReader<File>) -> () {
    input.lines()
        .filter_map(|result| result.ok())
        .filter_map(|s| Policy::from_str(&s).ok());
}

fn verify(policy: &Policy) -> bool {
    let count = policy.password.matches(policy.token).count();
    return count >= policy.min && count <= policy.max;
}

pub fn a(input: BufReader<File>) {
    let result = input.lines()
        .filter_map(|result| result.ok())
        .filter_map(|s| Policy::from_str(&s).ok())
        .filter(|p| verify(p))
        .count();
    println!("Answer to 02.A: {}", result);
}

pub fn b(input: BufReader<File>) {
    println!("Answer to 02.B: {}", "Not implemented!");
}

