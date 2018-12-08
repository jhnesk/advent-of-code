use std::env;
use std::io::{BufRead, BufReader};
use std::fs::File;
use std::collections::HashSet;

struct Step {
    before: char,
    after: char,
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let file = File::open(&args[1]).expect("cannot open file");
    let file = BufReader::new(file);

    let mut steps: HashSet<char> = HashSet::new();
    let mut instructions: Vec<Step> = Vec::new();
    let mut result: Vec<char> = Vec::new();

    for line in file.lines().filter_map(|result| result.ok()) {
        let chars: Vec<char> = line.chars().collect();
        instructions.push(Step { before: chars[5], after: chars[36] });
        steps.insert(chars[5]);
        steps.insert(chars[36]);
    }

    let mut remaining: Vec<&char> = steps.iter().collect::<Vec<&char>>();
    remaining.sort();

    let mut remove = '\0';
    while remaining.len() > 0 {
        for &r in &remaining {
            if ! instructions.iter().any(|x| x.after == *r) {
                instructions.retain(|x| x.before != *r);
                result.push(*r);
                remove=*r;
                break
            }
        }
        remaining.retain(|&x| x != &remove);
    }

    println!("7.1: {}", result.into_iter().collect::<String>());
}


