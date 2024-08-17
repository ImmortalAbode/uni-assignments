<%@page contentType="text/html"%>
<%@page pageEncoding="UTF-8"%>
<%@page import="java.util.ArrayList" %>

<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Главная страница</title>
    </head>
    <body>
        <jsp:useBean id="bean" scope="session" class="beans_jsp.MainBean" />
        <form action="MainPage.jsp" method="post">
            <label for="numbers">Введите последовательность чисел через пробел:</label><br/>
            <input type="text" name="numbers">
            <input type="submit" value="ОК">
        </form>
        <% 
            bean.setErrorMessage("");
            String numbers = request.getParameter("numbers");
            if (numbers != null && !numbers.isEmpty()) {
                bean.setNumbers(numbers);
                String[] numbersArray = numbers.split("\\s+");
                int evenNegativeSum = 0;
                int oddPositiveSum = 0;
                for (String number : numbersArray) {
                    try {
                        int num = Integer.parseInt(number);
                        if (num < 0 && num % 2 == 0) 
                        {
                            evenNegativeSum += num;
                        }
                        if (num > 0 && num % 2 != 0) 
                        {
                            oddPositiveSum += num;
                        }
                    } catch (NumberFormatException e) {
                        bean.setErrorMessage("Ошибка: " + e.getMessage());
                    }
                }
                bean.setEvenNegativeSum(evenNegativeSum);
                bean.setOddPositiveSum(oddPositiveSum);
                response.sendRedirect("FinishPage.jsp");
            }
        %>
        <%
            if (request.getParameter("fromFinishPage") != null) {
                bean.setTrigger(!bean.getTrigger());
            }
        %>
        <h3>Тригер на главной странице: <%= bean.getTrigger() %></h3>
    </body>
</html>