#![no_std]
use core::panic::PanicInfo;
use core::mem::MaybeUninit;
use core::slice::{
    from_raw_parts,
    from_raw_parts_mut,
};

#[no_mangle]
pub fn add_one(x: i32) -> i32 {
    x + 1
}

#[no_mangle]
pub fn matmul(
    n: i32, m: i32, k:i32,
    a: *const i32, b: *const i32, c: *mut i32
) -> i32 {
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
                        acc += a[i*m+l] * b[l*k+j]
                    }
                    c[i*k+j] = acc;
                }
            }
        }
        return c[0];
    }
}

#[no_mangle]
pub fn main() {
    let a: [i32; 10000] = [1; 10000];
    let b: [i32; 10000] = [1; 10000];
    let mut c: [i32; 10000] = unsafe { MaybeUninit::uninit().assume_init() };
    matmul(100, 100, 100, &a[0] as *const i32, &b[0] as *const i32, &mut c[0] as *mut i32);
}


#[no_mangle]
#[panic_handler]
pub fn panic(_info: &PanicInfo) -> ! { loop {} }
