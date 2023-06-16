
import java.util.Random;

public class programa1 {

	public static void main(String[] args) {
		int i = 5;
		int min_val = 1;
        int max_val = 5;
		Random ran = new Random();
        int x = ran.nextInt(max_val) + min_val;
		
		System.out.println("Hello word!!"+"\nvalor de  i=" +i);
			
		int valor;
		
		
		// ternario
		valor = (i > 4) ? i : 7;
		
		System.out.println("valor :"+valor);
		
		switch (x){
			case 5:
				System.out.println("case5 :" +x);break;
			case 2:
				System.out.println("case2 :" +x);break;
			case 1:
				System.out.println("case1 :" +x);break;
			case 3:
				System.out.println("case3 :" +x);break;
			case 4:
				System.out.println("case4 :" +x);
				break;
			default:
				break;
		}
	
	}

}
