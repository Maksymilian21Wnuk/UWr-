
fn square_area_to_circle(size:f64) -> f64 {
    //you answer
    let bok:f64 = size.sqrt();
    let r:f64 = bok / 2.0;
    f64::powf(r, 2.0) * 3.14159265358979
}

fn assert_close(a:f64, b:f64, epsilon:f64) {
    assert!( (a-b).abs() < epsilon, "Expected: {}, got: {}",b,a);
}

fn main(){
    assert_close(square_area_to_circle(9.0), 7.0685834705770345, 1e-8);
    assert_close(square_area_to_circle(20.0), 15.70796326794897, 1e-8);
    assert_close(square_area_to_circle(500.0), 392.7, 0.01);
    assert_close(square_area_to_circle(1.0), 0.7854, 0.0001);
    assert_close(square_area_to_circle(1000.0), 785.4, 0.1);
}