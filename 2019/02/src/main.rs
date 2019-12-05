use std::env;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::usize;

fn read_input() -> Vec<usize> {
    let args: Vec<String> = env::args().collect();
    let input = File::open(&args[1]).expect("Cannot open file");
    let input = BufReader::new(input);

    let line = input.lines().take(1)
        .filter_map(|result| result.ok())
        .collect::<String>();

    return line.split(',')
        .map(|s| s.parse::<usize>())
        .filter_map(|result| result.ok())
        .collect::<Vec<usize>>();
}

fn execute(mut program : Vec<usize>) -> usize {
    let mut i : usize = 0;

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

    return program[0];
}

fn main() {
    let mut program = read_input();

    // Restore the program!
    program[1] = 12;
    program[2] = 2;

    println!("{}", execute(program));
}
