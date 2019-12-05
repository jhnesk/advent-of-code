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
        let opcode = program[i];

        match opcode {
            1 => {
                let (a, b, c) = (program[i+1], program[i+2], program[i+3]);
                program[c] = program[a] + program[b];
                i = i + 4;
            },
            2 => {
                let (a, b, c) = (program[i+1], program[i+2], program[i+3]);
                program[c] = program[a] * program[b];
                i = i + 4;
            },
            99 => break,
            _ => panic!()
        }
    }
    println!("{}", program[0]);
}
