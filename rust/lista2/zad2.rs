use std::collections::HashSet;

fn sort_alphabet(s1 : &str, s2 : &str) -> String {
    let mut s: String = s1.to_owned() + s2;

    let mut l: Vec<char> = s.chars().collect();
    l.sort_unstable(); 
    l.dedup();
    

    l.into_iter().collect()
}

fn main() {

    assert_eq!(sort_alphabet("loopingisfunbutdangerous","lessdangerousthancoding" ),"abcdefghilnoprstu");
    assert_eq!(sort_alphabet("aretheyhere","yestheyarehere" ),"aehrsty");
    assert_eq!(sort_alphabet("acdbbbe", "xyz"), "abcdexyz");
    assert_eq!(sort_alphabet("xyaabbbccccdefww", "xxxxyyyyabklmopq"), "abcdefklmopqwxy");
    assert_eq!(sort_alphabet("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz");
    println!("Passed");

}
