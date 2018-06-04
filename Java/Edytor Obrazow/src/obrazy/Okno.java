package obrazy;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
public class Okno extends JFrame
{

    JToolBar pasek=new JToolBar();
    JButton wybierzPlik= new JButton("wybierz plik");
    JButton przybliz=new JButton(new ImageIcon("/Users/dejw/Documents/butt.png"));
    JButton oddal=new JButton(new ImageIcon("/Users/dejw/Documents/out.png"));
    PicturePanel panel=new PicturePanel();
    JScrollPane drawPane = new JScrollPane(panel);

    JButton prawo=new JButton(new ImageIcon("/Users/dejw/Documents/right.png")),lewo=new JButton(new ImageIcon("/Users/dejw/Documents/left.png")),gora=new JButton(new ImageIcon("/Users/dejw/Documents/up.png")),dol=new JButton(new ImageIcon("/Users/dejw/Documents/down.png"));


    private JList list;
    private DefaultListModel listModel;//lista 3 kolorow

    private ListSelectionListener listlistener=new ListSelectionListener()  //wybor koloru
    {
        public void valueChanged(ListSelectionEvent ev)
        {
            int indeks=list.getSelectedIndex();

            if(indeks==0)
            {
                kolory.setColor(Color.RED);
            }
            else if(indeks==1)
            {
                kolory.setColor(Color.GREEN);
            }

            else if(indeks==2)
            {
                kolory.setColor(Color.BLUE);
            }
        }
    };


    private MouseListener mouselist=new MouseAdapter()   //rysuje kropke
    {
        public void mouseClicked(MouseEvent ev)
        {
            panel.rysuj(ev.getX(), ev.getY(), kolory.getColor());
            panel.repaint();
        }

    };

    private MouseMotionListener mousemot= new MouseMotionAdapter()
    {
        public void mouseDragged(MouseEvent ev)
        {
            mouselist.mouseClicked(ev);
        }

        public void mouseMoved(MouseEvent ev)
        {
            wspolzedne.setText("wspolrzedna x: "+Integer.toString(ev.getX())+"   "+"wspolrzedna y: "+Integer.toString(ev.getY()));
            wspolzedne.updateUI();
        }
    };

    JLabel wspolzedne=new JLabel("wspolrzedne myszki"); // etykieta do wspolrzednych

    JColorChooser kolory=new JColorChooser(); // wyswietlam panel z kolorami

    Button kolor_but=new Button("SHOW ALL COLORS");// wywoluje jc chooser

    private ActionListener ShowColors = new ActionListener()   //po kliknieciu widac kolory
    {
        public void actionPerformed(ActionEvent ev)
        {
            kolory.setVisible(true);
        }
    };

    private ActionListener bPrawy = new ActionListener()
    {
        public void actionPerformed(ActionEvent ev)
        {
            drawPane.getHorizontalScrollBar().setValue(drawPane.getHorizontalScrollBar().getMaximum());
        }
    };

    private ActionListener bLewy = new ActionListener()
    {
        public void actionPerformed(ActionEvent ev)
        {
            drawPane.getHorizontalScrollBar().setValue(drawPane.getHorizontalScrollBar().getMinimum());
        }
    };

    private ActionListener bGora = new ActionListener()
    {
        public void actionPerformed(ActionEvent ev)
        {
            drawPane.getVerticalScrollBar().setValue(drawPane.getVerticalScrollBar().getMinimum());
        }
    };

    private ActionListener bDol = new ActionListener()
    {
        public void actionPerformed(ActionEvent ev)
        {

            drawPane.getVerticalScrollBar().setValue(drawPane.getVerticalScrollBar().getMaximum());
        }
    };

    public Okno()
    {
        super("Edytor obrazow");
        kolory.setVisible(false);  //chowam kolory na poczatku
        kolor_but.addActionListener(ShowColors);

        pasek.add(wybierzPlik); //dodaje wybierz plik do paska

        wybierzPlik.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                JFileChooser jFileChooser = new JFileChooser();
                if(jFileChooser.showOpenDialog(wybierzPlik)==JFileChooser.APPROVE_OPTION)
                {
                   panel.openImage(jFileChooser.getSelectedFile().getPath());
                }
            }
        });

        przybliz.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
               panel.zoom(panel.zoom+1);
               panel.repaint();
               drawPane.revalidate();
            }
        });

        prawo.addActionListener(bPrawy);
        lewo.addActionListener(bLewy);
        gora.addActionListener(bGora);
        dol.addActionListener(bDol);
        pasek.add(przybliz);
        pasek.add(oddal);

        oddal.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                panel.zoom(panel.zoom-1);
               panel.repaint();
               drawPane.revalidate();
            }
        });

        panel.addMouseListener(mouselist);
        panel.addMouseMotionListener(mousemot);


        pasek.add(lewo);
        pasek.add(prawo);
        pasek.add(gora);
        pasek.add(dol);

        add(wspolzedne,BorderLayout.SOUTH);
        add(pasek,BorderLayout.NORTH);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setLocation(100,100);
        setSize(1200,1200);

        listModel = new DefaultListModel();
        listModel.addElement("red");
        listModel.addElement("green");
        listModel.addElement("blue");


        //nowa lista


        list = new JList(listModel);
        list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        list.setSelectedIndex(0);
        list.addListSelectionListener(listlistener);
        list.setVisibleRowCount(5);
        JScrollPane listScrollPane = new JScrollPane(list);
        JPanel west=new JPanel(new GridLayout(3,1));
        west.add(listScrollPane);
        west.add(kolor_but);
        west.add(kolory);
        JSplitPane center=new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,west,drawPane); //rozdzielam
        add(center,BorderLayout.CENTER);




    }
}