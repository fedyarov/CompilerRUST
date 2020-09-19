fn main()
{
	let mut var1=2;
	let mut i=0;
	let mut j=0;

	for i in 1 .. 5{
		var1 = var1 * 2;
		println!("{}", var1);
		for j in 0 .. 2{
			var1 = var1+1;
			println!("{}",var1);
		}
	}

}