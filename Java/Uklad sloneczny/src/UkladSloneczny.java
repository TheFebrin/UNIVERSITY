import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class UkladSloneczny
{
    public static void main(String[] args)
    {
        new UkladSloneczny();
    }

    public UkladSloneczny() //okno
    {
                JFrame frame = new JFrame("UKLAD SLONECZNY");
                frame.setLayout(new BorderLayout());
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                PanelSloneczny panelSloneczny = new PanelSloneczny();
                frame.add(panelSloneczny, BorderLayout.CENTER);

                JToolBar toolBar = new JToolBar();
                JButton slower = new JButton("slow x2");
                JButton faster = new JButton("speed x2");

                slower.addActionListener(a -> panelSloneczny.speed *= 0.5);
                faster.addActionListener(a -> panelSloneczny.speed *= 2);

                toolBar.add(slower);
                toolBar.add(faster);

                frame.add(toolBar, BorderLayout.NORTH);
                frame.pack();
                frame.setVisible(true);
    }

    public enum Planety
    {
        Słońce(new Point(600, 500), 696342, Color.yellow),
        Merkury(Słońce, 57909036.f, 2439, 0.241, Color.LIGHT_GRAY),
        Wenus(Słońce, 108208925.f, 6051, 0.615, Color.CYAN),
        Ziemia(Słońce, 149597871.f, 6371, 1, Color.blue),
        Księżyc(Ziemia, 384400.f, 1736, 0.0748, Color.BLACK),
        Mars(Słońce, 227936637.f, 3389, 1.881, Color.orange),
        Jowisz(Słońce, 778412028.f, 70000, 11.862, Color.red),
        Saturn(Słońce, 1473838225.f, 60000, 29.457, Color.magenta),
        Uran(Słońce, 2872428721.f, 25362, 84.011, Color.GREEN),
        Neptun(Słońce, 4494967229.f, 24662, 164.69,Color.blue ),
        Ceres(Słońce, 414082773.f, 945, 4.6054,Color.pink ),
        Pluto(Słońce, 5906423142.f, 2370, 247.6,Color.CYAN ),
        Haumea(Słońce, 6483571729.f, 1379, 285.3,Color.RED ),
        Eris(Słońce, 10120295973.f, 2326, 556.4,Color.magenta ),
        Makemake(Słońce, 6845598576.f, 1500, 309.57,Color.DARK_GRAY ),
        Titan(Saturn, 1221870.f, 2575, 0.0438,Color.ORANGE ),
        Io(Jowisz, 421700.f, 1821, 0.00466,Color.green );

        Point pozycja;
        boolean CzyToSlonce;
        Planety center;
        double orbita;
        double promien;
        double okres;
        Color color;

        public int getX() {return (int) pozycja.getX();}
        public int getY() {return (int) pozycja.getY();}

        Planety(Planety center, double orbit, double radius, double period, Color color)  //dla planet
        {
            CzyToSlonce = false;
            this.center = center;
            this.pozycja = new Point();
            this.color = color;
            this.promien = Math.sqrt(radius) / 15;
            this.orbita = (Math.sqrt(orbit) / 50 + (Math.log10(orbit) - 5) * 50) * 0.195 + center.promien;
            this.okres = period * 365;
        }

        Planety(Point position, double radius, Color color)  //osobny do slonca
        {
            this.pozycja = position;
            this.CzyToSlonce = true;
            this.color = color;
            this.promien = Math.sqrt(radius) / 15;
        }

        void ActPosition(double angle)//akt pozycja
        {
            if (CzyToSlonce) return;  //slonce nie zmienia pozycji
            angle = angle / okres;
            double x = center.getX() + orbita * Math.sin(angle);
            double y = center.getY() + orbita * Math.cos(angle);
            pozycja.setLocation(x, y);
        }

    }
    public class PanelSloneczny extends JPanel
    {

        ArrayList<Planety> list = new ArrayList<Planety>();
        double angle = 0;
        double speed = 30;

        public PanelSloneczny()
        {
            list.add(Planety.Słońce);
            list.add(Planety.Merkury);
            list.add(Planety.Wenus);
            list.add(Planety.Ziemia);
            list.add(Planety.Księżyc);
            list.add(Planety.Mars);
            list.add(Planety.Eris);
            list.add(Planety.Jowisz);
            list.add(Planety.Saturn);
            list.add(Planety.Uran);
            list.add(Planety.Neptun);
            list.add(Planety.Pluto);
            list.add(Planety.Ceres);
            list.add(Planety.Haumea);
            list.add(Planety.Makemake);
            list.add(Planety.Titan);
            list.add(Planety.Io);

            Timer timer = new Timer(10, new ActionListener()
            {
                public void actionPerformed(ActionEvent e)  //odmalowywanie co dany czas
                {
                    repaint();
                }
            });
            timer.start();
        }

        protected void paintComponent(Graphics g)
        {
            super.paintComponent(g);
            angle += Math.PI * 2 * speed * 0.016;  //kat

                Graphics2D g2d = (Graphics2D) g.create();
                g2d.drawImage(null, 0, 0, this);

                for(int i = 0; i < list.size(); i++)
                {
                    list.get(i).ActPosition(angle);
                    g2d.setPaint(list.get(i).color);

                    int x=list.get(i).getX()-(int) list.get(i).promien;
                    int y=list.get(i).getY()-(int) list.get(i).promien;
                    int width=(int) list.get(i).promien * 2;
                    int height=(int) list.get(i).promien * 2;

                    g2d.fillOval(x, y, width, height);
                }
        }

        public Dimension getPreferredSize()
        {
            return new Dimension(1200, 1000);
        }
    }
}