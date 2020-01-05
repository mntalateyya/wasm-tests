#![no_std]
use core::panic::PanicInfo;

extern "C" {
    fn now() -> f64;
    fn alert(s: &str);
}

static A: [i16; 250000] = [1; 250000];
static B: [i16; 250000] = [1; 250000];
static mut C: [i16; 250000] = [0; 250000];

#[no_mangle]
pub fn matmul(size: i32) -> f64 {
    let a = &A[0] as *const i16;
    let b = &B[0] as *const i16;
    let c = unsafe { &mut C[0] as *mut i16 };
    let size = size as isize;
    unsafe {
        let start = now();
        for _ in 0..5 {
            for i in 0..size {
                for j in 0..size {
                    let mut acc = 0;
                    for l in 0..size {
                        acc += a.offset(i*size+l).read() * b.offset(l*size+j).read();
                    }
                    c.offset(i*size+j).write(acc);
                }
            }
        }
        let end = now();
        for i in 0..size {
            assert_eq!(c.offset(i*size + i).read(), size as i16);
        }
        end - start
    }
}

#[no_mangle]
#[panic_handler]
pub fn panic(_info: &PanicInfo) -> ! {
    unsafe { alert("Panic!") };
    loop {}
}
