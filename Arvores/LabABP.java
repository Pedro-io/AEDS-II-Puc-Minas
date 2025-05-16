
public class LabABP {

    public static void main(String[] args) throws Exception {
        ABP arvore = new ABP();
        arvore.inserir(7);
        arvore.inserir(13);
        arvore.inserir(4);
        arvore.inserir(5);
        arvore.inserir(17);
        arvore.inserir(1);
        arvore.caminhar();
        arvore.caminharPre();
        arvore.caminharPos();
        System.out.println(arvore.pesquisar(5));
        System.out.println(arvore.pesquisar(9));
        System.out.println(arvore.getAltura());
    }

    

}

