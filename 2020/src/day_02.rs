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

fn verify_a(policy: &Policy) -> bool {
    let count = policy.password.matches(policy.token).count();
    return count >= policy.min && count <= policy.max;
}

fn verify_b(policy: &Policy) -> bool {
    let first = policy.password.chars().nth(policy.min-1).unwrap();
    let second = policy.password.chars().nth(policy.max-1).unwrap();
    if(first == policy.token && second != policy.token) {
        return true;
    } else if (first != policy.token && second == policy.token) {
        return true;
    } else {
        return false;
    }
}

pub fn a(input: BufReader<File>) {
    let result = input.lines()
        .filter_map(|result| result.ok())
        .filter_map(|s| Policy::from_str(&s).ok())
        .filter(|p| verify_a(p))
        .count();
    println!("Answer to 02.A: {}", result);
}

pub fn b(input: BufReader<File>) {
    let result = input.lines()
        .filter_map(|result| result.ok())
        .filter_map(|s| Policy::from_str(&s).ok())
        .filter(|p| verify_b(p))
        .count();

    println!("Answer to 02.B: {}", result);
}


