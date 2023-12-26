fn get_count(string: &str) -> usize {
  let mut vowels_count: usize = 0;
  
  for c in string.chars(){
    match c{
        'a'|'e'|'i'|'o'|'u' => vowels_count += 1,
        _=>(),
    }
  }
  vowels_count
}
  


fn main(){
  let strs : [&str; 5] = ["asdfasdf", "a b d eee", "fffffffxyqwe", "mnytersd", "adsfasdfasdf"]; 

  let res : [usize;5] = [2, 4, 1, 1, 3];

  for i in 0..5{
    assert!(get_count(strs[i]) == res[i]);
  }
  println!("passed");


}


