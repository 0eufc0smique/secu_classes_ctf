- integers
    
    ```rust
    fn main() {
        println!("Hello, world!"); 
    
        println!("max size of a u32: {}", u32::MAX);
        println!("max size of a u128: {}", u128::MAX);
        println!("min size of a i128: {}", i128::MIN); 
        println!("max size of a f32: {}", f32::MAX);
    }
    ```
    
- type of variables
    
    ```rust
    const NUMBER: i32 = 18;
    
    fn main() {
    		let mut hello: &str = "hello world!";
        println!("{}", hello);
    
        hello = "hello again";
        println!("{}", hello);
        
        
        let x = 1;
        let y: i32 = 2;
        println!("x + y = {}", x+y);
    
        println!("number: {}", NUMBER);
    }
    ```
    
- scope and shadowing
    
    ```rust
    #![allow(unused)]
    
    fn main() {
    	let x = 1;
        let y: i32 = 3;
        let y: i32 = 2;
        {
            println!("x + y = {}", x+y);
        } 
        println!("x + y = {}", x+y);
    }
    ```
    
- suffixes and underscores
    
    ```rust
    fn main() {
        let x: f32 = 42_000f32;
        let y: i32 = 1_000_000;
    
        println!("x = {}", x);
        println!("y = {}", y);
    }
    ```
    
- tuples
    
    ```rust
    fn main() {
        // COMPOUND TYPES - tuples & arrays
        // max value of tuple = 12
        let student_a = ("jeremy", "A", 3.8);
        /* let student_name = student_a.0;
        let student_grade = student_a.1;
        let student_gpa = student_a.2; */
        let (student_name, student_grade, student_gpa) = student_a;
        println!("my name is {} my grade is {} my gpa is {}", student_name, student_grade, student_gpa);
    }
    ```
    
- arrays
    
    ```rust
    fn main() {
        // ARRAYS - [] - store 32 values - similar datatypes
        let students = ["heath", "bob", "linda"];
        println!("first student is {}", students[0]);
    }
    ```
    
- slices
    
    ```rust
    fn main() {
        // SLICES - debug format {:?}
    
        let mut arr = [1,2,3,4,5];
        let slice = &mut arr[1..3];
        println!("{:?}", slice);
        
        /* let slice = &arr[4..5];
        println!("{:?}", slice); */
    
        slice[0] = 6;
        slice[1] = 7;
        println!("{:?}", arr);
    }
    
    // [2, 3]
    // [1, 6, 7, 4, 5]
    ```
    
- strings
    
    ```rust
    // STRINGS - several types - mostly used 2 : String and str
    // str - string slice, &str - borrowed string slice - immutable
    // String - eap-allocated, owned, mutable string
    // &str = string slice, borrowed, read-only immutable, often used to pass string data between functions or to extract substrings from a larger string.
    //-----------------------------------------------------------------------------
    fn main() {
        let mut name = "toto";
        name.push_str("     test");
        println!("{}", name);
    }
    // ERROR push_str doesn't exist
    //-----------------------------------------------------------------------------
    fn main() {
        let mut name = String::new();            // creates an empty, mutable String
        name.push_str("     test");              // push_str() appends a string slice (&str) to the end of the String.
        println!("{}", name);
    }
    // WORKS push_str exists
    //-----------------------------------------------------------------------------
    fn main() {
        let mut name: String = String::new();
        name.push_str("im");
        name.push_str(" toto");
        name.push_str("     test");
        println!("{}", name);
    }
    //-----------------------------------------------------------------------------
    fn main() {
        let name = "toto".to_string();            // converts the &str into a heap-allocated String => owned and mutable
        println!("{}", name);
        let name: String = String::from("toto");  // create a String from a &str, allocates a new String with the same value as the input string slice.
    																					    // creates a new variable that shadows the previous name
        println!("{}", name);
    }
    ```
