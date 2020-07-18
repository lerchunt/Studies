package downloader.src.downloader.ui;

import downloader.src.downloader.fc.Downloader;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import javax.swing.*;
public class Main extends JFrame{
    JTextField texte;
     StackLayout sl;
     JPanel container,pan1,pan2;
     JProgressBar b;
	public Main(){
            super("Downloader");
            
            container = new JPanel();
            container.setLayout(new BorderLayout());
            sl = new StackLayout();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            
            pan1= new JPanel();
            //pan1.setLayout(sl);
            sl.layoutContainer(pan1);
            pan1.setPreferredSize(new Dimension(800, 300));
            
            container.add(pan1,BorderLayout.CENTER);
            
            texte = new JTextField();
            //texte.setSize(500, 20);
            texte.setColumns(40);
            JButton button = new JButton("add");
            
            button.addActionListener(new java.awt.event.ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    
                    String url = texte.getText();
                    Downloader d  = new Downloader(url);
                    
                    JPanel pantmp = new JPanel();
                    pan1.add(pantmp);
                    b = new JProgressBar();
                    pantmp.add(b);
                    
                    
                    Thread th = new Thread(new Runnable() {
                    
                        public void run() {
                            try{ 
                                d.addPropertyChangeListener(new PropertyChangeListener(){ 
                                    @Override
                                    public void propertyChange(PropertyChangeEvent evt) {
        
                                        b.setValue(d.getProgress());
                                        b.setStringPainted(true);
                                    }
                                 
                                });
                                d.download();
                            }catch (Exception ex) {
                                
                            }
                         }
                    });
                    th.start();
                    pack();
                }
            });
            
            pan2 = new JPanel();
            pan2.setLayout(new FlowLayout());
            pan2.add(texte,FlowLayout.LEFT );
            pan2.add(button,FlowLayout.CENTER);
            
            container.add(pan2,BorderLayout.SOUTH);
            
            add(container);
            pack();
	}
	
	public static void main(String[] args){
		JFrame fen = new Main();
                fen.setVisible(true);
                
	}
	
}