
package br.com.secao12;
/**
 *
 * @author silas
 */
public class Progama28 {
    public static void main(String [] args){
        Aluno p1 = new Aluno("caio silas", 2000, "000.000");
        
        System.out.println(p1);
        
        Aluno a1 = new Aluno ("maria",2002,"123456");
        System.out.println(a1);
        
        Professor proff = new Professor("alexandre",1995,"PROF123");
        System.out.println(proff);
    }
}
