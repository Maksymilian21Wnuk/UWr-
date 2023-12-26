
fn gimme_the_letters(sp: &str) -> String{
    let char_vec: Vec<char> = sp.chars().collect();
    let mut res = String::from("");  
    for i in char_vec[0] ..= char_vec[2]{
        res.push(i);
    }
    res
}




fn main(){
    assert_eq!(gimme_the_letters("a-z"), "abcdefghijklmnopqrstuvwxyz");
    assert_eq!(gimme_the_letters("h-o"), "hijklmno");
    assert_eq!(gimme_the_letters("Q-Z"), "QRSTUVWXYZ");
    assert_eq!(gimme_the_letters("J-J"), "J");
    assert_eq!(gimme_the_letters("a-b"), "ab");
    assert_eq!(gimme_the_letters("A-A"), "A");
    assert_eq!(gimme_the_letters("g-i"), "ghi");
    assert_eq!(gimme_the_letters("H-I"), "HI");
    assert_eq!(gimme_the_letters("y-z"), "yz");
    assert_eq!(gimme_the_letters("e-k"), "efghijk");
    assert_eq!(gimme_the_letters("a-q"), "abcdefghijklmnopq");
    assert_eq!(gimme_the_letters("F-O"), "FGHIJKLMNO");
    println!("passed");
}