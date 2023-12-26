

fn count_bits(n: i64) -> u32 {
    n.count_ones()
  }


fn main(){
    assert_eq!(count_bits(0), 0);
    assert_eq!(count_bits(4), 1);
    assert_eq!(count_bits(7), 3);
    assert_eq!(count_bits(9), 2);
    assert_eq!(count_bits(10), 2);
    assert_eq!(count_bits(0xffff), 16);
    assert_eq!(count_bits(0xf0f0), 8);
    assert_eq!(count_bits(0xf00feeee), 20);
    println!("passed");
}