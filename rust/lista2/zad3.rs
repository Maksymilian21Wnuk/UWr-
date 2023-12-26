

fn summy(strng: &str) -> i32{
    let sep = strng.split(" ");
    let mut sum:i32 = 0;
    for t in sep{
        sum += t.parse::<i32>().unwrap();
    }
    sum
}



fn main(){
    assert_eq!(summy("1 2 3"), 6);
    assert_eq!(summy("1 2 3 4"), 10);
    assert_eq!(summy("1 2 3 4 5"), 15);
    assert_eq!(summy("10 10"), 20);
    assert_eq!(summy("0 0"), 0);
    assert_eq!(summy("1 1 1 1 1 1 1 1 1 1 1 1 1 1"), 14);
    assert_ne!(summy("1 1 1"), 2);
    println!("passed");
}