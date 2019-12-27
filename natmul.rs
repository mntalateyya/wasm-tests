use std::slice::{
    from_raw_parts,
    from_raw_parts_mut,
};

pub fn add_one(x: i32) -> i32 {
    x + 1
}

pub fn matmul(
    n: i32, m: i32, k:i32,
    a: *const i32, b: *const i32, c: *mut i32
) {
    let (n, m, k) = (n as usize, m as usize, k as usize);
    unsafe {
        let a = from_raw_parts(a, n*m);
        let b = from_raw_parts(b, m*k);
        let c = from_raw_parts_mut(c, n*k);
        for _ in 0..300 {
            for i in 0..n {
                for j in 0..k {
                    let mut acc = 0;
                    for l in 0..m {
                        acc += a.get_unchecked(i*m+l) * b.get_unchecked(l*k+j);
                    }
                    *c.get_unchecked_mut(i*k+j) = acc;
                }
            }
        }
    }
}

pub fn main() {
    let mut argv = std::env::args();
    argv.next();
    let n = argv.next().unwrap().parse::<usize>().unwrap();
    let m1 = argv.next().unwrap().parse::<usize>().unwrap();
    let m2 = argv.next().unwrap().parse::<usize>().unwrap();
    let k = argv.next().unwrap().parse::<usize>().unwrap();
    assert_eq!(m1, m2);
    let a = vec![0; n*m1];
    let b = vec![0; m1*k];
    let mut c = Vec::with_capacity(n*k);
    unsafe { c.set_len(n*k); }
    matmul(n as i32, m1 as i32, k as i32,
        &a[0] as *const i32, &b[0] as *const i32, &mut c[0] as *mut i32);
    std::process::exit(c[0]);
}
