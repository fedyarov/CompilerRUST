fn main()
{
	let mut var1=0;
	let mut var2=10;
	let mut var3=98;
	let mut i=0;

	var1 = ((((25-5)*5)/2)+50)-var3;
	println!("{}",var1);

	for i in 1 .. 5{
		var1 = var1 * 2;
		println!("{}", var1);
	}

	if var1 == 32 {
		for i in 0 .. 3{
			var1 = var1/2;
			println!("{}",var1);
		}
	}

	if var2 < var1*2 {
		println!("{}",var2);
	}
	else {
		let mut temp=var2;
		var2 = var1;
		var1 = temp;
		println!("{}",var1);
		println!("{}",var2);
	}

}