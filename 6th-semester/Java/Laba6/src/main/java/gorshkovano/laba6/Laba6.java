package gorshkovano.laba6;


import java.util.*;
import java.awt.*;
import java.awt.event.*;

class OurWindowAdapter extends WindowAdapter {
    public void windowClosing (WindowEvent wE) {
        System.exit (0);
    }
}

class Laba6 extends Frame {

    int count = 0;
    java.util.List<Integer> id_figures = new ArrayList<Integer>();
    java.util.List<Figure> figures = new ArrayList<Figure>(); 
    Frame f ;
    Canvas cnv;
    
    Label lTypeFigure, lColorFigure, lSpeedFigure, lIDFigure, lIDFigure2, lNewIDFigure, lNewSpeedFigure;
    Button bAddFigure, bChangeFigure;
    Choice cColorFigure, cIDFigure;
    TextField tfTypeFigure, tfIDFigure, tfNewIDFigure, tfSpeedFigure, tfNewSpeedFigure;
    
    Color color;

    Laba6() {
        //Управляющее окно.
        this.setLocation(200, 150);
        this.setSize(new Dimension(300,300));
        this.setTitle("Управляющее окно");      
 
        //Тип фигуры.
        lTypeFigure = new Label("Тип фигуры: ");
        tfTypeFigure = new TextField();        
        //ID фигуры.
        lIDFigure = new Label("ID фигуры: ");        
        tfIDFigure = new TextField();        
        //Цвет фигуры.
        lColorFigure = new Label("Цвет фигуры: ");        
        cColorFigure = new Choice();
        cColorFigure.addItem("Синий");
        cColorFigure.addItem("Зелёный");
        cColorFigure.addItem("Красный");
        cColorFigure.addItem("Чёрный");
        cColorFigure.addItem("Жёлтый");       
        //Скорость фигуры.
        lSpeedFigure = new Label("Скорость фигуры: ");        
        tfSpeedFigure = new TextField();
        //Кнопка добавить.
        bAddFigure = new Button("Добавить");
        bAddFigure.setActionCommand("Add");       
        //ID фигуры для изменения.
        lIDFigure2 = new Label("ID фигуры: ");        
        cIDFigure = new Choice();     
        //Новый ID фигуры.
        lNewIDFigure = new Label("Новый ID фигуры: ");        
        tfNewIDFigure = new TextField();        
        //Новая скорость фигуры.
        lNewSpeedFigure = new Label("Новая скорость фигуры: ");        
        tfNewSpeedFigure = new TextField();        
        //Кнопка изменить.
        bChangeFigure = new Button("Изменить");
        bChangeFigure.setActionCommand("Change");

        cnv = new Canvas() {
            public void paint(Graphics g) {
                //
            }
        };

        GridBagConstraints gbc = new GridBagConstraints();
        this.setLayout (new GridBagLayout());

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0; gbc.gridy = 0;
        this.add (lTypeFigure, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 1; gbc.gridy = 0;
        this.add (tfTypeFigure, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0; gbc.gridy = 1;
        this.add (lIDFigure, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 1; gbc.gridy = 1;
        this.add (tfIDFigure, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0; gbc.gridy = 2;
        this.add (lColorFigure, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 1; gbc.gridy = 2;
        this.add (cColorFigure, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0; gbc.gridy = 3;
        this.add (lSpeedFigure, gbc);
        
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 1; gbc.gridy = 3;
        this.add (tfSpeedFigure, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0; gbc.gridy = 4; gbc.gridwidth = 2;
        this.add (bAddFigure, gbc);
        
        gbc.gridwidth = 1;
        //Пропуск пространства
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0; gbc.gridy = 5;
        this.add(new Label(""), gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0; gbc.gridy = 6;
        this.add (lIDFigure2, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 1; gbc.gridy = 6;
        this.add (cIDFigure, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0; gbc.gridy = 7;
        this.add (lNewIDFigure, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 1; gbc.gridy = 7;
        this.add (tfNewIDFigure, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0; gbc.gridy = 8;
        this.add (lNewSpeedFigure, gbc);
        
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 1; gbc.gridy = 8;
        this.add (tfNewSpeedFigure, gbc);
        
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0; gbc.gridy = 9; gbc.gridwidth = 2;
        this.add (bChangeFigure, gbc);

        bAddFigure.addActionListener(new ActionListener() {
            public void actionPerformed (ActionEvent aE) {
                AddButFunc();
            }
        });

        bChangeFigure.addActionListener(new ActionListener() {
            public void actionPerformed (ActionEvent aE) {
                ChangeButFunc();
            }
        });

        this.addWindowListener (new OurWindowAdapter());

        //Демонстрационное окно.
        f = new Frame();
        f.setTitle("Демонстрационное окно");
        f.addWindowListener(new OurWindowAdapter());
        f.setSize(500,500);
        f.add(cnv);
        f.setVisible(true);
        f.setLocation(600, 150);
        f.setResizable(false);
    }

    public void AddButFunc() {
        if (IsInteger(tfIDFigure.getText()) && IsInteger(tfSpeedFigure.getText())) { //проверка скорости
            if (CheckColor(cColorFigure.getSelectedItem())) { //проверка цвета
                int num = Integer.parseInt(tfIDFigure.getText());
                int foundNumber = -1;
                for (int i = 0; i < count; i++) { //поиск объекта
                    if (id_figures.get(i) == num)
                        foundNumber = i;
                }
                if (foundNumber == -1 && CheckFigure(tfTypeFigure.getText(), num)) {
                    id_figures.add(num);
                    count++;
                    cIDFigure.addItem(id_figures.get(count-1) + "");
                    figures.get(count-1).start();
                }
            }
        }
    }

    public void ChangeButFunc() {
        int old_num = Integer.parseInt(cIDFigure.getSelectedItem());

        int foundNumber = -1;
        for (int i = 0; i < count; i ++) { //поиск объекта
            if (id_figures.get(i) == old_num)
                foundNumber = i;
        }
        if (IsInteger(tfNewIDFigure.getText())) {
            int foundNumber2 = -1;
            int new_num = Integer.parseInt(tfNewIDFigure.getText());
            for (int i = 0; i < count; i ++) { //поиск объекта
                if (id_figures.get(i) == new_num)
                    foundNumber2 = i;
            }
            if (foundNumber2 == -1)
            {
                for (int i = 0; i < cIDFigure.getItemCount(); i++){
                    if (Integer.parseInt(cIDFigure.getItem(i)) == old_num){
                        cIDFigure.remove(i);
                        cIDFigure.add(tfNewIDFigure.getText() + "");
                        break;
                    }
                }
                id_figures.set(foundNumber, Integer.valueOf(tfNewIDFigure.getText()));
                figures.get(foundNumber).id = Integer.parseInt(tfNewIDFigure.getText()); // изменение id
            }
            
        }
        if (IsInteger(tfNewSpeedFigure.getText())){
                figures.get(foundNumber).speed = Integer.parseInt(tfNewSpeedFigure.getText()); // изменение скорости
            }
    }

    public boolean IsInteger(String string) {
        try {
            Integer.parseInt(string);
        }
        catch (Exception e) {
            return false;
        }
        return true;
    }

    public boolean CheckFigure(String fgr, int id) {
        if (fgr.equalsIgnoreCase("круг")) {
            figures.add(new Circle(this.cnv, color, Integer.parseInt(tfSpeedFigure.getText()), id));
        }
        else if (fgr.equalsIgnoreCase("квадрат")) {
            figures.add(new Quadrangle(this.cnv, color, Integer.parseInt(tfSpeedFigure.getText()), id));
        }
        else if (fgr.equalsIgnoreCase("овал")) {
            figures.add(new Oval(this.cnv, color, Integer.parseInt(tfSpeedFigure.getText()), id));
        }
        else if (fgr.equalsIgnoreCase("прямоугольник")) {
            figures.add(new Rectangle(this.cnv, color, Integer.parseInt(tfSpeedFigure.getText()), id));
        }
        else if (fgr.equalsIgnoreCase("треугольник")) {
            figures.add(new Triangle(this.cnv, color, Integer.parseInt(tfSpeedFigure.getText()), id));
        }
        else {
            return false;
        }
        return true;
    }


    public boolean CheckColor(String clr) {
        if (clr.equalsIgnoreCase("красный")) {
            this.color = Color.red;
        }
        else if (clr.equalsIgnoreCase("синий")) {
            this.color = Color.blue;
        }
        else if (clr.equalsIgnoreCase("жёлтый")) {
            this.color = Color.yellow;
        }
        else if (clr.equalsIgnoreCase("зелёный")) {
            this.color = Color.green;
        }
        else if (clr.equalsIgnoreCase("чёрный")) {
            this.color = Color.black;
        }
        else
            return false;

        return true;
    }

    public static void main (String[] args) {
        Laba6 Fr = new Laba6();
        Fr.show();
    }
}

abstract class Figure extends Thread{
    Point point = new Point(50, 50);
    Canvas cnv;
    Graphics g;
    Color color;
    public int speed;
    double angle;
    int id;
    int step = 4;

    void moveTo() {
        this.show(g, false);
        this.point.x += this.speed*Math.cos(this.angle)*step;
        this.point.y += this.speed*Math.sin(this.angle)*step;
        checkBorder();
        this.show(g, true);
    }

    void show(Graphics g, boolean sh) {
        //
    }

    void checkBorder() {
        //
    }

    public void run() {
        while(true) {
            moveTo();
            try {
                sleep(130);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Circle extends Figure{
    int radius = 15;

    void show(Graphics g, boolean sh) {
        if (sh)
            g.setColor(color);
        else
            g.setColor(Color.white);

        g.fillOval(point.x, point.y, radius, radius);
        g.drawString(this.id + "", point.x, point.y);
    }

    void checkBorder() {
        boolean border = false;
        int dd = 5;
        //фигура достигла правой границы холста
        if ((cnv.getWidth()-point.x <= this.radius + dd) && (Math.cos(this.angle) > 0)) {
            this.angle = Math.PI - this.angle;
            border = true;
        }
        //фигура достигла левой границы холста
        else if ((point.x <= 0 + dd) && (Math.cos(this.angle) < 0)) {
            this.angle = Math.PI - this.angle;
            border = true;
        }
        //фигура достигла нижней границы холста
        if ((cnv.getHeight()-point.y <= this.radius + dd) && (Math.sin(this.angle) > 0)) {
            this.angle *= (-1);
            border = true;
        }
        //фигура достигла верхней границы холста
        else if ((point.y <= 0 + dd) && (Math.sin(this.angle) < 0)) {
            this.angle *= (-1);
            border = true;
        }

        if (border) {
            this.point.x += this.speed*Math.cos(this.angle);
            this.point.y += this.speed*Math.sin(this.angle);
        }
    }

    Circle(Canvas cnv, Color color, int speed, int id) {
        this.cnv = cnv;
        this.color = color;
        this.speed = speed;
        this.angle = Math.random()*2*Math.PI;
        this.g = cnv.getGraphics();
        this.id = id;
    }
}
class Quadrangle extends Figure{

    int height = 15;

    void show(Graphics g, boolean sh) {
        if (sh)
            g.setColor(color);
        else
            g.setColor(Color.white);

        g.fillRect(point.x-height/2, point.y-height/2, height, height); // используется вычитание height/2, чтобы верхний левый угол прямоугольника был расположен в точке (point.x, point.y), а не в его центре
        g.drawString(this.id + "", point.x-height/2-2, point.y-height/2-2);
    }

    void checkBorder() {
        boolean border = false;
        int dd = 5;
        if ((cnv.getWidth()-point.x <= this.height/2 + dd) && (Math.cos(this.angle) > 0)) {
            this.angle = Math.PI - this.angle;
            border = true;
        }
        else if ((point.x <= this.height/2 + dd) && (Math.cos(this.angle) < 0)) {
            this.angle = Math.PI - this.angle;
            border = true;
        }

        if ((cnv.getHeight()-point.y <= this.height/2 + dd) && (Math.sin(this.angle) > 0)) {
            this.angle *= (-1);
            border = true;
        }
        else if ((point.y <= this.height/2 + dd) && (Math.sin(this.angle) < 0)) {
            this.angle *= (-1);
            border = true;
        }

        if (border) {
            this.point.x += this.speed*Math.cos(this.angle);
            this.point.y += this.speed*Math.sin(this.angle);
        }
    }

    Quadrangle(Canvas cnv, Color color, int speed, int id) {
        this.cnv = cnv;
        this.color = color;
        this.speed = speed;
        this.angle = Math.random()*2*Math.PI;
        this.g = cnv.getGraphics();
        this.id = id;
    }
}

class Oval extends Figure {
    int majorAxis;
    int minorAxis;

    Oval(Canvas cnv, Color color, int speed, int id) {
        this.cnv = cnv;
        this.color = color;
        this.speed = speed;
        this.angle = Math.random() * 2 * Math.PI;
        this.g = cnv.getGraphics();
        this.id = id;
        this.majorAxis = 30;
        this.minorAxis = 15;
    }

    void show(Graphics g, boolean sh) {
        if (sh)
            g.setColor(color);
        else
            g.setColor(Color.white);

        g.fillOval(point.x, point.y, majorAxis, minorAxis);
        g.drawString(this.id + "", point.x, point.y);
    }

    void checkBorder() {
        boolean border = false;
        int dd = 5;
        // Проверка правой границы холста
        if ((cnv.getWidth() - point.x <= majorAxis / 2 + dd) && (Math.cos(angle) > 0)) {
            angle = Math.PI - angle;
            border = true;
        }
        // Проверка левой границы холста
        else if ((point.x <= majorAxis / 2 + dd) && (Math.cos(angle) < 0)) {
            angle = Math.PI - angle;
            border = true;
        }

        // Проверка нижней границы холста
        if ((cnv.getHeight() - point.y <= minorAxis / 2 + dd) && (Math.sin(angle) > 0)) {
            angle = -angle;
            border = true;
        }
        // Проверка верхней границы холста
        else if ((point.y <= minorAxis / 2 + dd) && (Math.sin(angle) < 0)) {
            angle = -angle;
            border = true;
        }

        if (border) {
            point.x += speed * Math.cos(angle);
            point.y += speed * Math.sin(angle);
        }
    }
}

class Triangle extends Figure {
    int base;
    int height;

    Triangle(Canvas cnv, Color color, int speed, int id) {
        this.cnv = cnv;
        this.color = color;
        this.speed = speed;
        this.angle = Math.random() * 2 * Math.PI;
        this.g = cnv.getGraphics();
        this.id = id;
        this.base = 20;
        this.height = 15;
    }

    double area() {
        return 0.5 * base * height;
    }

    void show(Graphics g, boolean sh) {
        if (sh)
            g.setColor(color);
        else
            g.setColor(Color.white);

        int[] xPoints = {point.x, point.x - base / 2, point.x + base / 2};
        int[] yPoints = {point.y - height / 2, point.y + height / 2, point.y + height / 2};
        g.fillPolygon(xPoints, yPoints, 3);
        g.drawString(this.id + "", point.x, point.y);
    }

    void checkBorder() {
        boolean border = false;
        int dd = 5;
        int[] xPoints = {point.x, point.x - base / 2, point.x + base / 2};
        int[] yPoints = {point.y - height / 2, point.y + height / 2, point.y + height / 2};

        for (int i = 0; i < 3; i++) {
            // Проверка правой границы холста
            if ((cnv.getWidth() - xPoints[i] <= dd) && (Math.cos(angle) > 0)) {
                angle = Math.PI - angle;
                border = true;
            }
            // Проверка левой границы холста
            else if ((xPoints[i] <= dd) && (Math.cos(angle) < 0)) {
                angle = Math.PI - angle;
                border = true;
            }
            // Проверка нижней границы холста
            if ((cnv.getHeight() - yPoints[i] <= dd) && (Math.sin(angle) > 0)) {
                angle = -angle;
                border = true;
            }
            // Проверка верхней границы холста
            else if ((yPoints[i] <= dd) && (Math.sin(angle) < 0)) {
                angle = -angle;
                border = true;
            }
        }

        if (border) {
            point.x += speed * Math.cos(angle);
            point.y += speed * Math.sin(angle);
        }
    }
}

class Rectangle extends Figure {
    int width;
    int height;

    Rectangle(Canvas cnv, Color color, int speed, int id) {
        this.cnv = cnv;
        this.color = color;
        this.speed = speed;
        this.angle = Math.random() * 2 * Math.PI;
        this.g = cnv.getGraphics();
        this.id = id;
        this.width = 30;
        this.height = 20;
    }

    double area() {
        return width * height;
    }

    void show(Graphics g, boolean sh) {
        if (sh)
            g.setColor(color);
        else
            g.setColor(Color.white);

        g.fillRect(point.x - width / 2, point.y - height / 2, width, height);
        g.drawString(this.id + "", point.x - width / 2 - 2, point.y - height / 2 - 2);
    }

    void checkBorder() {
        boolean border = false;
        int dd = 5;

        // Проверка правой границы холста
        if ((cnv.getWidth() - point.x <= width / 2 + dd) && (Math.cos(angle) > 0)) {
            angle = Math.PI - angle;
            border = true;
        }
        // Проверка левой границы холста
        else if ((point.x <= width / 2 + dd) && (Math.cos(angle) < 0)) {
            angle = Math.PI - angle;
            border = true;
        }
        // Проверка нижней границы холста
        if ((cnv.getHeight() - point.y <= height / 2 + dd) && (Math.sin(angle) > 0)) {
            angle = -angle;
            border = true;
        }
        // Проверка верхней границы холста
        else if ((point.y <= height / 2 + dd) && (Math.sin(angle) < 0)) {
            angle = -angle;
            border = true;
        }

        if (border) {
            point.x += speed * Math.cos(angle);
            point.y += speed * Math.sin(angle);
        }
    }
}
