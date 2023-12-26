fn string_to_number(s: &str) -> i32 {
    s.parse().unwrap()
  }



fn main(){
    assert_eq!(string_to_number("1234"), 1234);
    assert_eq!(string_to_number("605"), 605);
    assert_eq!(string_to_number("1405"), 1405);
    assert_eq!(string_to_number("-7"), -7);
    assert_eq!(string_to_number("-1000000"), -1000000);
    assert_eq!(string_to_number("2147483647"), 2147483647);
    print!("done\n");
}