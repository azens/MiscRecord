class FatherClass {
	public FatherClass() {
		System.out.println(100);
	}
	public FatherClass(int age) {
		System.out.println(age);
	}
}
class main1 extends FatherClass {
	public main1() {
		// super();
	}
	public  main1(int c) {
		super(c);
		//System.out.println(1234);
	}
	public static void main(String[] args) {
		new FatherClass();
		new FatherClass(28);
		new main1();
		new main1(66);
	}
}