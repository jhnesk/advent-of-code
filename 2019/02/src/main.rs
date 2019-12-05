use std::env;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::usize;

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = File::open(&args[1]).expect("Cannot open file");
    let input = BufReader::new(input);

    let line = input.lines().take(1)
        .filter_map(|result| result.ok())
        .collect::<String>();

    let mut program : Vec<usize> = line.split(',') 
        .map(|s| s.parse::<usize>())
        .filter_map(|result| result.ok())
        .collect();

    let mut i : usize = 0;

    // Restore the program!
    program[1] = 12;
    program[2] = 2;

    loop {
        let instruction = program[i];

        match instruction {
            1 => {
                let index_a = program[i+1];
                let index_b = program[i+2];
                let index_out = program[i+3];
                program[index_out] = program[index_a] + program[index_b];
            },
            2 => {
                let index_a = program[i+1];
                let index_b = program[i+2];
                let index_out = program[i+3];
                program[index_out] = program[index_a] * program[index_b];
            },
            99 => break,
            _ => panic!()
        }
        i = i + 4;
    }
    println!("{}", program[0]);
}
