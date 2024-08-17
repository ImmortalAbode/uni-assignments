import java.io.IOException;
import java.io.PrintWriter;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.util.ArrayList;

/**
 * http://localhost:8080/Laba7/myServlet?data=-5 -5 61 33 -6 -4 1&name=Горшков Андрей Олегович&groupNumber=4312&resetTextSize=30
 * @author Andrew
 */
@WebServlet(urlPatterns =  {"/myServlet"})
public class myServlet extends HttpServlet {
    static int requestsCount; 
    static int textSize;
    static int minTextSize;
    public myServlet() {
        myServlet.requestsCount = 0;
        myServlet.textSize = 20;
        myServlet.minTextSize = 10;        
    }
    
    ArrayList<Integer> lab1Result(String args) 
    {
        //Массив с результирующими суммами.
        ArrayList<Integer> resultList = new ArrayList<>();
        //Получение данных для вычисления.
        String[] numbers = args.split(" ");
        int evenNegativeSum = 0;
        int oddPositiveSum = 0;
        for (String numStr : numbers) 
        {
            int num = Integer.parseInt(numStr);
            if (num < 0 && num % 2 == 0) 
            {
                evenNegativeSum += num;
            }
            if (num > 0 && num % 2 != 0) 
            {
                oddPositiveSum += num;
            }
        }
        //Добавление результрующих сумм в массив.
        resultList.add(evenNegativeSum);
        resultList.add(oddPositiveSum);
        //Возврат результата.
        return resultList;
    }
    
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException 
    {
        response.setContentType("text/html;charset=UTF-8");
        //Увеличение счетчика обращений к странице сервлета после его запуска.
        myServlet.requestsCount++;
        //Обработка URL-параметров.
        String resetTextSize = request.getParameter("resetTextSize");
        String name = request.getParameter("name");
        String groupNumber = request.getParameter("groupNumber");
        if (resetTextSize != null && resetTextSize.matches("[1-9]\\d*")) 
        {
            myServlet.textSize = Integer.parseInt(resetTextSize);//Если параметр-сброс активен, то сбрасываем к значению по умолчанию.
        } 
        else if (myServlet.textSize >= minTextSize) 
        {
            myServlet.textSize--;//Иначе уменьшение размера текста в таблице.
        }
        //Формирование HTML-страницы.
        try (PrintWriter out = response.getWriter()) 
        {
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Лабораторная работа №7. Сервлеты.</title>");
            //Отображение ФИО и группы студента на WEB-странице.
            out.println("<h1>Студент: " + name + "</h1>");
            out.println("<h1>Группа: " + groupNumber + "</h1>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Servlet myServlet at " + request.getContextPath() + "</h1>");
            out.println("</body>");
            out.println("</html>");
            //Отображение значений счетчика обращений к странице сервлета после его запуска.
            out.println("<h3>requestsСount: " + myServlet.requestsCount + "</h3>");
            //Обновление размера текста в таблице страницы сервлета при обращении.
            if (myServlet.textSize < myServlet.minTextSize) 
            {
                out.println("<h3>Дальнейшее уменьшение размера текста в таблице невозможно.</h3>");
            }
            
            String data = request.getParameter("data"); 
            if (data != null && !data.trim().isEmpty()) {
                ArrayList<Integer> labResult = lab1Result(data);
                out.println("<table style='border:1px solid black; font-size:" + myServlet.textSize + "px;'>");
                
                out.println("<tr>");
                out.println("<td style='border:1px solid black;'>Ввели</td>");
                for (String input : data.split(" ")) {
                    out.println("<td style='border:1px solid black;'>" + input + "</td>");
                }
                out.println("</tr>");
                
                out.println("<tr>");
                out.println("<td style='border:1px solid black;'>Сумма четных и отрицательных чисел</td>");
                out.println("<td style='border:1px solid black;'>" + labResult.get(0) + "</td>");
                out.println("</tr>");
                
                out.println("<tr>");
                out.println("<td style='border:1px solid black;'>Сумма нечетных и положительных чисел</td>");
                out.println("<td style='border:1px solid black;'>" + labResult.get(1) + "</td>");
                out.println("</tr>");
                
                out.println("</table>");
            }
            out.println("</body>");
            out.println("</html>");
        }
    }
    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException 
    {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException 
    {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() 
    {
        return "Short description";
    }// </editor-fold>
}