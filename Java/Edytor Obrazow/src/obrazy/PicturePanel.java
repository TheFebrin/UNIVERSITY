package obrazy;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JPanel;



public class PicturePanel extends JPanel
{

    BufferedImage originalImage;
    BufferedImage bufferedImage;

    int zoom=1;//przechowuje aktualne przyblizenie

    public void zoom(int zoom) // przyblizanie obrazu
    {
            this.zoom = zoom;
            bufferedImage = new BufferedImage(originalImage.getWidth()*zoom, originalImage.getHeight()*zoom, BufferedImage.TYPE_INT_ARGB);
            bufferedImage.getGraphics().drawImage(originalImage, 0, 0, bufferedImage.getWidth(), bufferedImage.getHeight(), null);
            setPreferredSize(new Dimension(bufferedImage.getWidth(),bufferedImage.getHeight()));
    }

    public void openImage(String filepath) //otwieranie obrazu
    {
        try
        {
            originalImage = ImageIO.read(new File(filepath));

        } catch (IOException e)
        {
            System.err.println(e);
            System.exit(1);
        }

        originalImage.createGraphics().drawImage(originalImage, 0, 0, originalImage.getWidth(), originalImage.getHeight(), null);
        zoom(1);
        setPreferredSize(new Dimension(bufferedImage.getWidth(), bufferedImage.getHeight()));
        repaint();
    }
    public PicturePanel() //obraz bazowy
    {
        openImage("/Users/dejw/Documents/ddd.jpg");
    }

    public void rysuj(int x, int y, Color c) //rysowanie po obrazie
    {
        Graphics2D g = originalImage.createGraphics();
        g.setPaint(c);
        g.drawRect(x/zoom,y/zoom,0,0);
        zoom(zoom);
    }
    protected void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        g.drawImage(bufferedImage, 0, 0, this);
    }
}