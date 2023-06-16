
package com.mycompany.tp2;
import java.util.ArrayList;

/**
 *
 * @author silas
 */
public class Eletronico extends Livro {
    private String url;
    private String formatoArquivo;
    
    public Eletronico(String url,String formatoArquivo,ArrayList escritores,String titulo, ArrayList capitulos, int anoPublicacao, String idiomaOriginal, ArrayList keywords){
        super(escritores,titulo,capitulos,anoPublicacao,idiomaOriginal,keywords);
        this.url = url;
        this.formatoArquivo = formatoArquivo;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getFormatoArquivo() {
        return formatoArquivo;
    }

    public void setFormatoArquivo(String formatoArquivo) {
        this.formatoArquivo = formatoArquivo;
    }
    
    
}
