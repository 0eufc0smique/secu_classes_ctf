use rand::Rng;

const CHARSET: &[u8] = b"ABCDEFGHIJKLMNOPQRSTUVWXYZ\
                        abcdefghijklmnopqrstuvwxyz\
                        0123456789)(*&^%$#@!~+-=_[]{}|";
const PASSWORD_LEN: usize = 20;

fn main() {
    let mut rng = rand::thread_rng();                   // creates a random number generator, using its own thread

    let password: String = (0..PASSWORD_LEN)            // creates an iterator that goes from 0 to PASSWORD_LEN - 1
        .map(|_| {                                      // map = iterator adaptor transforming each item in the iterator
            let idx = rng.gen_range(0..CHARSET.len());  // the easiest way to execute code within the thread is to use a closure
            CHARSET[idx] as char
        })
        .collect();

    println!("{:?}", password);
}