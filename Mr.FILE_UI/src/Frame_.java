import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

class ImagePanel extends JPanel{
	private Image img;
	public ImagePanel(Image img) {
		this.img = img;	
		//setting size
		setSize(new Dimension(img.getWidth(null),img.getHeight(null)));
		setPreferredSize(new Dimension(img.getWidth(null),img.getHeight(null)));
		setLayout(null);
	}
	public void paintComponent(Graphics g) {
		g.drawImage(img,0,0,null);
	}
	
}

public class Frame_{

	public static void FrameSet(JFrame frame, ImagePanel panel) {
		frame.setVisible(true);
		frame.getContentPane().add(panel);
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	public static void ButtonSet(JButton button) {
		button.setVisible(true);
		button.setBackground(Color.white);
		button.setOpaque(false);
		button.setBorderPainted(false);
	}
	

	public static void FrameStart() {
		JFrame frame = new JFrame("<File_S> Start");
		ImagePanel panel = new ImagePanel(new ImageIcon("./image/01_START.PNG").getImage());
		FrameSet(frame,panel);
		//frame.setSize(401, 565);
		frame.setLocationRelativeTo(null);
		
		JButton button1 = new JButton("");
		ButtonSet(button1);
		button1.setSize(240,80);
		button1.setLocation(80,400);
		panel.add(button1);
	
		button1.addActionListener(new ActionListener() {
		
			@Override
			public void actionPerformed(ActionEvent e) {
				
				FrameMenu();
				frame.dispose();	
			}
		});
		
	}
	
	public static void FrameMenu() {
		JFrame frame = new JFrame("<File_S> Menu");
		ImagePanel panel = new ImagePanel(new ImageIcon("./image/02_MENU.PNG").getImage());
		//frame.setSize(182, 453);
		FrameSet(frame,panel);
		frame.setLocationRelativeTo(null);
		
		JButton button1 = new JButton("");
		JButton button2 = new JButton("");
		JButton button3 = new JButton("");
		
		ButtonSet(button1);
		ButtonSet(button2);
		ButtonSet(button3);
		
		button1.setSize(130,130);
		button1.setLocation(135,68);
		
		button2.setSize(130,130);
		button2.setLocation(135,220);
		
		button3.setSize(130,130);
		button3.setLocation(135,375);
		
		panel.add(button1);
		panel.add(button2);
		panel.add(button3);
		
		button1.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				
				FrameUserSetting();
				frame.dispose();	
			}
		});
		
		button2.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				
				//지은이 실행파일
				frame.dispose();	
			}
		});
		
		button3.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				
				FrameRecieve();
				frame.dispose();	
			}
		});
		
		
	
	}
	static String ip1,ip2,ip3 = "";
	public static void FrameUserSetting() {
		
		JFrame frame = new JFrame("<File_S> User Setting");
		ImagePanel panel = new ImagePanel(new ImageIcon("./image/03_USER_SETTINGS.PNG").getImage());
		//frame.setSize(404, 566);
		FrameSet(frame,panel);
		frame.setLocationRelativeTo(null);


		JTextField textfield1 = new JTextField(15);
		JTextField textfield2 = new JTextField(15);
		JTextField textfield3 = new JTextField(15);
		
		TextFieldSet(textfield1);
		textfield1.setSize(175,36);
		textfield1.setLocation(120,176);
		textfield1.setText(ip1);
		panel.add(textfield1);
		
		TextFieldSet(textfield2);
		textfield2.setSize(175,36);
		textfield2.setLocation(120,270);
		textfield2.setText(ip2);
		panel.add(textfield2); 
		
		TextFieldSet(textfield3);
		textfield3.setSize(175,36);
		textfield3.setLocation(120,362);
		textfield3.setText(ip3);
		panel.add(textfield3);
		
		JButton button1 = new JButton("");
		JButton button2 = new JButton("");
		JButton button3 = new JButton("");
		
		ButtonSet(button1);
		button1.setSize(36,36);
		button1.setLocation(327,176);
		panel.add(button1);
		
		button1.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				
				FrameMenu();
				frame.dispose();	
				ip1 = textfield1.getText();
				ip2 = textfield2.getText();
				ip3 = textfield3.getText();
			}
		});
		
		ButtonSet(button2);
		button2.setSize(36,36);
		button2.setLocation(327,270);
		panel.add(button2);
		
		button2.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				
				FrameMenu();
				frame.dispose();	
				ip1 = textfield1.getText();
				ip2 = textfield2.getText();
				ip3 = textfield3.getText();
			
			}
		});
		
		ButtonSet(button3);
		button3.setSize(36,36);
		button3.setLocation(327,362);
		panel.add(button3);
		
		button3.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				
				FrameMenu();				
				frame.dispose();		
				ip1 = textfield1.getText();
				ip2 = textfield2.getText();
				ip3 = textfield3.getText();
			}
		});
		
	}
	private static void TextFieldSet(JTextField textfield) {
		
		textfield.setVisible(true);
		textfield.setOpaque(false);
		textfield.setBorder(null); 
	}

	public static void FrameRecieve() {
		JFrame frame = new JFrame("<File_S> Recieve");
		ImagePanel panel = new ImagePanel(new ImageIcon("./image/04_RECIEVE.PNG").getImage());
		
		//frame.setSize(404, 566);
		FrameSet(frame,panel);
		frame.setLocationRelativeTo(null);
	}
	
	public static void main(String[] args) {

	//FrameRecieve();
	//FrameUserSetting();
	//FrameMenu();
	FrameStart();
	
	}
}
