package kreski;

import java.awt.*;
import java.awt.event.*;
import java.util.LinkedList;

class Okno extends Frame
{
    private Color kolor = Color.BLACK;
    Point p;
    boolean CzyMyszkaOkno=true;
    private LinkedList<Kreska> lista=new LinkedList<Kreska>(); //lista przechowujaca kreski

    private class ZdarzeniaOkno extends WindowAdapter
    {
        public void windowClosing(WindowEvent ev)
        {
            Okno.this.dispose();
        }
    };


    private MouseListener mouseList = new MouseAdapter()
    {
        @Override
        public void mousePressed(MouseEvent ev)
        {
            p=ev.getPoint();
            lista.add(new Kreska(p,p,Color.WHITE));
        }
        public void mouseExited(MouseEvent ev)
        {
            CzyMyszkaOkno=false;
        }
        public void mouseEntered(MouseEvent ev) {
            CzyMyszkaOkno=true;
            if(p!=null) {
                lista.add(new Kreska(p,p,Color.WHITE));
                }
        }
        public void mouseReleased(MouseEvent ev)
        {
            if(CzyMyszkaOkno)
            {
               lista.remove(lista.size()-1);
                Point koniec=ev.getPoint();
                Kreska kreska=new Kreska(p,koniec,kolor);
                lista.add(kreska);
                Graphics graph=plotno.getGraphics();
                graph.setColor(kreska.kolor);
                graph.drawLine(kreska.begg.x,kreska.begg.y,kreska.end.x,kreska.end.y);
            }
        }
    };
    private KeyListener keyList = new KeyAdapter()
    {
        @Override
        public void keyPressed (KeyEvent ev)
        {
            Graphics gr  = plotno.getGraphics();
            switch (ev.getKeyCode()){
                case KeyEvent.VK_BACK_SPACE:
                    gr.clearRect(0, 0, plotno.getWidth(), plotno.getHeight());
                    lista=new LinkedList<Kreska>();
                    break;
                case KeyEvent.VK_F:
                    gr.clearRect(0, 0, plotno.getWidth(), plotno.getHeight());
                    if(lista.size()>0)
                    {
                        lista.remove(0);
                        for(int i=0;i<lista.size();i++) {
                            Kreska kreska=lista.get(i);
                            gr.setColor(kreska.kolor);
                            gr.drawLine(kreska.begg.x, kreska.begg.y, kreska.end.x, kreska.end.y);
                        }
                    }
                    break;
                case KeyEvent.VK_L:
                    gr.clearRect(0, 0, plotno.getWidth(), plotno.getHeight());
                    if(lista.size()>0)
                    {
                        lista.remove(lista.size()-1);
                        for(int i=0;i<lista.size();i++) {
                            Kreska kreska=lista.get(i);
                            gr.setColor(kreska.kolor);
                            gr.drawLine(kreska.begg.x, kreska.begg.y, kreska.end.x, kreska.end.y);
                        }
                    }
                    break;
            }

        }

    };

    private Canvas plotno = new Canvas();

    private CheckboxGroup cbg = new CheckboxGroup();
    private Checkbox orange = new Checkbox("orange",cbg,false);
    private Checkbox red = new Checkbox("red",cbg,false);
    private Checkbox blue = new Checkbox("blue",cbg,false);
    private Checkbox green = new Checkbox("green",cbg,false);
    private Checkbox black = new Checkbox("black",cbg,true);
    private Panel west = new Panel(new GridLayout(10,1));

    public Okno()
    {
        super("kolorowe kreski");
        setSize(800, 400);
        setLocation(100, 100);
        add(plotno, BorderLayout.CENTER);
        plotno.addKeyListener(keyList);
        plotno.addMouseListener(mouseList);
        addWindowListener(new ZdarzeniaOkno());
        plotno.setFocusable(true);
        plotno.requestFocus();

        setVisible(true);



        west.add(orange);
        west.add(red);
        west.add(blue);
        west.add(green);
        west.add(black);
        add(west,BorderLayout.WEST);



        orange.addItemListener(new ItemListener(){
            public void itemStateChanged(ItemEvent e) {
                if(e.getStateChange()==1) {
                    kolor=Color.ORANGE;
                }
            }
        });
        red.addItemListener(new ItemListener(){
            public void itemStateChanged(ItemEvent e) {
                if(e.getStateChange()==1) {
                    kolor=Color.RED;
                }
            }
        });


        blue.addItemListener(new ItemListener(){
            public void itemStateChanged(ItemEvent e) {
                if(e.getStateChange()==1) {
                    kolor=Color.BLUE;
                }
            }
        });
        green.addItemListener(new ItemListener(){
            public void itemStateChanged(ItemEvent e) {
                if(e.getStateChange()==1) {
                    kolor=Color.GREEN;
                }
            }
        });
        black.addItemListener(new ItemListener(){
            public void itemStateChanged(ItemEvent e) {
                if(e.getStateChange()==1) {
                    kolor=Color.BLACK;
                }
            }
        });
    }


}

