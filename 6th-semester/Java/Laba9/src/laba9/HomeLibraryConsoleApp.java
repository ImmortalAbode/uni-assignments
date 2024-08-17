package laba9;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.Types;

import java.util.HashMap;
import java.util.Map;

import java.util.Scanner;

public class HomeLibraryConsoleApp {
    private static final String JDBC_URL = "jdbc:derby://localhost:1527/databases/HomeLibrary;user=db_user;password=db_user";
    private static final String TABLE_BOOK_LOCATION = "BookLocation";
    private static final String TABLE_BOOK_INFO = "BookInfo";
    private static final Map<String, String> bookInfoValues = new HashMap<>();
    private static final Map<String, String> bookLocationValues = new HashMap<>();

    public static void main(String[] args) {
        //bookInfo table
        bookInfoValues.put("author_full_name", "Default Author");
        bookInfoValues.put("publication_title", "Default Title");
        bookInfoValues.put("publisher", "Default Publisher");
        bookInfoValues.put("year_of_publication", "1999");
        bookInfoValues.put("number_of_pages", "150");
        bookInfoValues.put("year_of_writing", "1995");
        bookInfoValues.put("weight_in_grams", "500");
        //bookLocation table
        bookLocationValues.put("floor", "10");
        bookLocationValues.put("shelf", "10");
        bookLocationValues.put("rack", "10");
        try (Connection connection = DriverManager.getConnection(JDBC_URL)) {
            System.out.println("Connected to the database.");

            Scanner scanner = new Scanner(System.in);
            
            while(true) {
                System.out.println("\nChoose an option:");
                System.out.println("1. View all records");
                System.out.println("2. Add a new record");
                System.out.println("3. Update a record");
                System.out.println("4. Delete a record");
                System.out.println("5. Reset non-key fields");
                System.out.println("6. View the publishers in the specified shelf in lexicographic order");
                System.out.println("7. View the shortest and longest publication in terms of number of pages on the specified floor");
                System.out.println("8. View all shelves in lexicographic order");
                System.out.println("9. Exit");
                
                if (scanner.hasNextInt()) {
                    int choice = scanner.nextInt();
                    scanner.nextLine();
                    switch (choice) {
                        case 1 -> viewAllRecords(connection);
                        case 2 -> addNewRecord(connection);
                        case 3 -> updateRecord(connection);
                        case 4 -> deleteRecord(connection);
                        case 5 -> resetNonKeyFields(connection);
                        case 6 -> viewPublishersOnShelf(connection);
                        case 7 -> viewShortestLongestPublication(connection);
                        case 8 -> viewAllShelves(connection);
                        case 9 -> {
                            System.out.println("Exiting the application.");
                            return;
                        }
                        default -> System.out.println("Invalid choice. Please enter a valid option.");
                    }
                } else {
                    System.out.println("Invalid input. Please enter a valid integer.");
                    scanner.nextLine(); // Очищаем буфер ввода
                }
            }
        } catch (SQLException e) {
            System.err.println("Error connecting to the database: " + e.getMessage());
        }
    }
    //Print header of all exist records.
    private static void viewAllRecords(Connection connection) throws SQLException {
        String bookInfoSql = "SELECT * FROM " + TABLE_BOOK_INFO;
        try (Statement bookInfoStatement = connection.createStatement();
                ResultSet bookInfoResultSet = bookInfoStatement.executeQuery(bookInfoSql)) {
            System.out.println("\nAll records from BookInfo table:");
            System.out.printf("| %-5s | %-5s | %-15s | %-20s | %-20s | %-15s | %-10s | %-15s | %-10s | %-5s | %-5s | %-5s |\n",
                    "No.", "ID", "Author", "Title", "Publisher", "Year Pub", "Pages", "Year Writing", "Weight", "Floor", "Shelf", "Rack");
            System.out.println("|-------|-------|-----------------|----------------------|----------------------|-----------------|------------|-----------------|------------|-------|-------|-------|");
            printRecords(connection, bookInfoResultSet);
        }
    }
    //Print all exist records.
    private static void printRecords(Connection connection, ResultSet bookInfoResultSet) throws SQLException {
        int currentIndex = 1;
        while (bookInfoResultSet.next()) {
            int bookInfoId = bookInfoResultSet.getInt("id");
            String bookLocationSql = "SELECT * FROM " + TABLE_BOOK_LOCATION + " WHERE id = ?";
            try (PreparedStatement bookLocationStatement = connection.prepareStatement(bookLocationSql)) {
                bookLocationStatement.setInt(1, bookInfoId);
                try (ResultSet bookLocationResultSet = bookLocationStatement.executeQuery()) {
                    if (bookLocationResultSet.next()) {
                        int yearOfWriting = bookInfoResultSet.getInt("year_of_writing");
                        String yearOfWritingValue = (bookInfoResultSet.wasNull()) ? "-" : String.valueOf(yearOfWriting);

                        System.out.printf("| %-5d | %-5d | %-15s | %-20s | %-20s | %-15d | %-10d | %-15s | %-10d | %-5d | %-5d | %-5d |\n",
                                currentIndex++,
                                bookInfoId,
                                bookInfoResultSet.getString("author_full_name"),
                                bookInfoResultSet.getString("publication_title"),
                                bookInfoResultSet.getString("publisher"),
                                bookInfoResultSet.getInt("year_of_publication"),
                                bookInfoResultSet.getInt("number_of_pages"),
                                yearOfWritingValue,
                                bookInfoResultSet.getInt("weight_in_grams"),
                                bookLocationResultSet.getInt("floor"),
                                bookLocationResultSet.getInt("shelf"),
                                bookLocationResultSet.getInt("rack"));
                    }
                }
            }
        }
    }
    //Add row in DB.
    private static void addNewRecord(Connection connection) throws SQLException {
        Scanner scanner = new Scanner(System.in);
        try {
            //Disable autocommit to rollback an add transaction if it fails.
            connection.setAutoCommit(false);

            String authorFullName;
            do {
                System.out.print("Enter author's full name: ");
                authorFullName = scanner.nextLine();
            } while (authorFullName.isEmpty());

            String publicationTitle;
            do {
                System.out.print("Enter publication title: ");
                publicationTitle = scanner.nextLine();
            } while (publicationTitle.isEmpty());

            String publisher;
            do {
                System.out.print("Enter publisher: ");
                publisher = scanner.nextLine();
            } while (publisher.isEmpty());
            
            System.out.print("Enter year of publication: ");
            int yearOfPublication = scanner.nextInt();
            System.out.print("Enter number of pages: ");
            int numberOfPages = scanner.nextInt();

            System.out.print("Enter year of writing (or leave empty for unknown):");
            scanner.nextLine();
            String yearOfWritingInput = scanner.nextLine();
            Integer yearOfWriting = null;
            if (yearOfWritingInput.isEmpty()) {
            } else {
                yearOfWriting = Integer.valueOf(yearOfWritingInput);
            }

            System.out.print("Enter weight in grams: ");
            int weightInGrams = scanner.nextInt();

            System.out.print("Enter floor number: ");
            int floorNumber = scanner.nextInt();
            System.out.print("Enter shelf number: ");
            int shelfNumber = scanner.nextInt();
            System.out.print("Enter rack number: ");
            int rackNumber = scanner.nextInt();

            int maxBookId = getMaxId(connection, TABLE_BOOK_INFO, "id");
            int maxLocationId = getMaxId(connection, TABLE_BOOK_LOCATION, "id");

            String bookInfoSql = "INSERT INTO " + TABLE_BOOK_INFO
                    + " (id, author_full_name, publication_title, publisher, year_of_publication, "
                    + "number_of_pages, year_of_writing, weight_in_grams) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
            try (PreparedStatement bookInfoStatement = connection.prepareStatement(bookInfoSql)) {
                bookInfoStatement.setInt(1, maxBookId + 1);
                bookInfoStatement.setString(2, authorFullName);
                bookInfoStatement.setString(3, publicationTitle);
                bookInfoStatement.setString(4, publisher);
                bookInfoStatement.setInt(5, yearOfPublication);
                bookInfoStatement.setInt(6, numberOfPages);
                if (yearOfWriting != null) {
                    bookInfoStatement.setInt(7, yearOfWriting);
                } else {
                    bookInfoStatement.setNull(7, Types.INTEGER);
                }
                bookInfoStatement.setInt(8, weightInGrams);
                int rowsInserted = bookInfoStatement.executeUpdate();
                System.out.println(rowsInserted + " record(s) inserted into BookInfo table.");
            }

            String bookLocationSql = "INSERT INTO " + TABLE_BOOK_LOCATION
                    + " (id, floor, shelf, rack) VALUES (?, ?, ?, ?)";
            try (PreparedStatement bookLocationStatement = connection.prepareStatement(bookLocationSql)) {
                bookLocationStatement.setInt(1, maxLocationId + 1);
                bookLocationStatement.setInt(2, floorNumber);
                bookLocationStatement.setInt(3, shelfNumber);
                bookLocationStatement.setInt(4, rackNumber);
                int rowsInserted = bookLocationStatement.executeUpdate();
                System.out.println(rowsInserted + " record(s) inserted into BookLocation table.");
            }
        } catch (java.util.InputMismatchException e) {
            System.out.println("Error: Invalid input format. Please enter integers in all fields except 'Author's Full Name', 'Publishing Name' and 'Publisher'.");
            scanner.next();
            connection.rollback();
        } finally {
            //Включение автокоммита транзакции.
            connection.setAutoCommit(true);
        }
    }
    //Get max ID of any table.
    private static int getMaxId(Connection connection, String tableName, String idColumnName) throws SQLException {
        String sql = "SELECT MAX(" + idColumnName + ") FROM " + tableName;
        try (Statement statement = connection.createStatement();
                ResultSet resultSet = statement.executeQuery(sql)) {
            if (resultSet.next()) {
                return resultSet.getInt(1);
            }
        }
        return 0;
    }
    //Update row in DB.
    private static void updateRecord(Connection connection) throws SQLException {
        viewAllRecords(connection);
        System.out.println();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the number of the record you want to update: ");

        try {
            int recordNumber = scanner.nextInt();
            scanner.nextLine();

            int id = getIdFromRecordNumber(connection, recordNumber);
            if (id == -1) {
                System.out.println("The record with the specified number was not found in the 'HomeLibrary' database. Check that the number you entered is correct and try again.");
                return;
            }

            //Отключение автокоммита для отката транзакции обновления в случае неудачи.
            connection.setAutoCommit(false);

            System.out.print("Enter new author's full name: ");
            String authorFullName = scanner.nextLine();
            System.out.print("Enter new publication title: ");
            String publicationTitle = scanner.nextLine();
            System.out.print("Enter new publisher: ");
            String publisher = scanner.nextLine();
            System.out.print("Enter new year of publication: ");
            int yearOfPublication = scanner.nextInt();
            System.out.print("Enter new number of pages:");
            int numberOfPages = scanner.nextInt();

            System.out.print("Enter year of writing (or leave empty for unknown):");
            scanner.nextLine();
            String yearOfWritingInput = scanner.nextLine();
            Integer yearOfWriting = null;
            if (yearOfWritingInput.isEmpty()) {
            } else {
                yearOfWriting = Integer.valueOf(yearOfWritingInput);
            }

            System.out.print("Enter new weight in grams: ");
            int weightInGrams = scanner.nextInt();

            System.out.print("Enter new floor number: ");
            int floorNumber = scanner.nextInt();
            System.out.print("Enter new shelf number: ");
            int shelfNumber = scanner.nextInt();
            System.out.print("Enter new rack number: ");
            int rackNumber = scanner.nextInt();

            String bookInfoSql = "UPDATE " + TABLE_BOOK_INFO + " SET author_full_name = ?, "
                    + "publication_title = ?, publisher = ?, year_of_publication = ?, "
                    + "number_of_pages = ?, year_of_writing = ?, weight_in_grams = ? WHERE id = ?";
            try (PreparedStatement bookInfoStatement = connection.prepareStatement(bookInfoSql)) {
                bookInfoStatement.setString(1, authorFullName);
                bookInfoStatement.setString(2, publicationTitle);
                bookInfoStatement.setString(3, publisher);
                bookInfoStatement.setInt(4, yearOfPublication);
                bookInfoStatement.setInt(5, numberOfPages);
                if (yearOfWriting != null) {
                    bookInfoStatement.setInt(6, yearOfWriting);
                } else {
                    bookInfoStatement.setNull(6, Types.INTEGER);
                }
                bookInfoStatement.setInt(7, weightInGrams);
                bookInfoStatement.setInt(8, id);
                int rowsUpdated = bookInfoStatement.executeUpdate();
                System.out.println(rowsUpdated + " record(s) updated in BookInfo table.");
            }

            String bookLocationSql = "UPDATE " + TABLE_BOOK_LOCATION + " SET floor = ?, "
                    + "shelf = ?, rack = ? WHERE id = ?";
            try (PreparedStatement bookLocationStatement = connection.prepareStatement(bookLocationSql)) {
                bookLocationStatement.setInt(1, floorNumber);
                bookLocationStatement.setInt(2, shelfNumber);
                bookLocationStatement.setInt(3, rackNumber);
                bookLocationStatement.setInt(4, id);
                int rowsUpdated = bookLocationStatement.executeUpdate();
                System.out.println(rowsUpdated + " record(s) updated in BookLocation table.");
            }
            //Коммит транзакции.
            connection.commit();
        } catch (java.util.InputMismatchException e) {
            System.out.println("Error: Invalid input format. Please enter the entry number as an integer.");
            scanner.next();
            connection.rollback();
        } finally {
            //Включение автокоммита транзакции.
            connection.setAutoCommit(true);
        }
    }
    //Delete row in DB.
    private static void deleteRecord(Connection connection) throws SQLException {
        viewAllRecords(connection);
        System.out.println();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the number of the record you want to delete: ");
        try {
            int recordNumber = scanner.nextInt();

            int id = getIdFromRecordNumber(connection, recordNumber);
            if (id == -1) {
                System.out.println("The record with the specified number was not found in the 'HomeLibrary' database. Check that the number you entered is correct and try again.");
                return;
            }

            //Отключение автокоммита для отката транзакции удаления в случае неудачи.
            connection.setAutoCommit(false);
            try {
                String bookInfoSql = "DELETE FROM " + TABLE_BOOK_INFO + " WHERE id = ?";
                try (PreparedStatement bookInfoStatement = connection.prepareStatement(bookInfoSql)) {
                    bookInfoStatement.setInt(1, id);
                    int rowsDeletedBookInfo = bookInfoStatement.executeUpdate();
                    System.out.println(rowsDeletedBookInfo + " record(s) deleted from BookInfo table.");
                }
                String bookLocationSql = "DELETE FROM " + TABLE_BOOK_LOCATION + " WHERE id = ?";
                try (PreparedStatement bookLocationStatement = connection.prepareStatement(bookLocationSql)) {
                    bookLocationStatement.setInt(1, id);
                    int rowsDeletedBookLocation = bookLocationStatement.executeUpdate();
                    System.out.println(rowsDeletedBookLocation + " record(s) deleted from BookLocation table.");
                }
                //Коммит транзакции.
                connection.commit();
            } catch (SQLException e) {
                System.out.println("A transaction execution error occurred. The transaction was cancelled.");
                connection.rollback();
            } finally {
                //Включение автокоммита транзакции.
                connection.setAutoCommit(true);
            }
        } catch (java.util.InputMismatchException e) {
            System.out.println("Error: Invalid input format. Please enter the entry number as an integer.");
            scanner.next();
        }
    }
    //Get ID from found row of any table.
    private static int getIdFromRecordNumber(Connection connection, int lineNumber) throws SQLException {
        String sql = "SELECT id FROM " + TABLE_BOOK_INFO + " ORDER BY id OFFSET ? ROWS FETCH FIRST 1 ROW ONLY";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, lineNumber - 1);
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt("id");
                }
            }
        }
        return -1;
    }
    //Reset non-key fields of row to DEFAULT values.
    private static void resetNonKeyFields(Connection connection) throws SQLException {
        viewAllRecords(connection);
        System.out.println();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter number of the record you want to reset: ");
        try {
            int recordNumber = scanner.nextInt();
            int id = getIdFromRecordNumber(connection, recordNumber);
            if (id == -1) {
                System.out.println("Record not found for the given line number.");
                return;
            }
            //Отключение автокоммита для отката транзакции сброса в случае неудачи.
            connection.setAutoCommit(false);
            
            // Обновление таблицы BookInfo
            for (Map.Entry<String, String> entry : bookInfoValues.entrySet()) {
                String key = entry.getKey();
                String value = entry.getValue();

                String sql = "UPDATE BookInfo SET " + key + " = ? WHERE id = ?";
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setString(1, value);
                    statement.setInt(2, id);
                    int rowsUpdated = statement.executeUpdate();
                    System.out.println(rowsUpdated + " record(s) updated for " + key + " in BookInfo table.");
                }
            }
            // Обновление таблицы BookLocation
            for (Map.Entry<String, String> entry : bookLocationValues.entrySet()) {
                String key = entry.getKey();
                String value = entry.getValue();

                String sql = "UPDATE BookLocation SET " + key + " = ? WHERE id = ?";
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setString(1, value);
                    statement.setInt(2, id);
                    int rowsUpdated = statement.executeUpdate();
                    System.out.println(rowsUpdated + " record(s) updated for " + key + " in BookLocation table.");
                }
            }
        } catch (java.util.InputMismatchException e) {
            System.out.println("Error: Invalid input format. Please enter the entry number as an integer.");
            scanner.next();
            connection.rollback();
        } finally {
            //Включение автокоммита транзакции.
            connection.setAutoCommit(true);
        }
    }
    //View the publishers in the specified shelf in lexicographic order.
    private static void viewPublishersOnShelf(Connection connection) throws SQLException {
        Scanner scanner = new Scanner(System.in);
        int floor;
        while (true) {
            try {
                System.out.print("Enter the floor number: ");
                floor = Integer.parseInt(scanner.nextLine());
                break;
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a valid integer.");
            }
        }
        
        int shelf;
        while (true) {
            try {
                System.out.print("Enter the shelf number: ");
                shelf = Integer.parseInt(scanner.nextLine());
                break;
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a valid integer.");
            }
        }

        String sql = "SELECT publisher FROM " + TABLE_BOOK_INFO + " INNER JOIN " + TABLE_BOOK_LOCATION +
                     " ON " + TABLE_BOOK_INFO + ".id = " + TABLE_BOOK_LOCATION + ".id WHERE floor = ? AND shelf = ? ORDER BY publisher";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, floor);
            statement.setInt(2, shelf);
            ResultSet resultSet = statement.executeQuery();
            System.out.println("\nPublishers in shelf " + shelf + ":");
            while (resultSet.next()) {
                System.out.println(resultSet.getString("publisher"));
            }
        }
    }
    //View the shortest and longest publication in terms of number of pages on the specified floor.
    private static void viewShortestLongestPublication(Connection connection) throws SQLException {
        Scanner scanner = new Scanner(System.in);
        int floor;
        while (true) {
            try {
                System.out.print("Enter the floor number: ");
                floor = Integer.parseInt(scanner.nextLine());
                break;
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a valid integer.");
            }
        }
        String SortestPublicationsql = "SELECT BI.publication_title, BI.number_of_pages " +
             "FROM " + TABLE_BOOK_INFO + " BI " +
             "INNER JOIN " + TABLE_BOOK_LOCATION + " BL ON BI.id = BL.id " +
             "WHERE BL.floor = ? " +
             "ORDER BY BI.number_of_pages ASC FETCH FIRST 1 ROWS ONLY";
        
        try (PreparedStatement statement = connection.prepareStatement(SortestPublicationsql)) {
            statement.setInt(1, floor);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                System.out.println("\nShortest publication on the floor " + floor + ":");
                System.out.println(resultSet.getString("publication_title") + " consists of " + resultSet.getInt("number_of_pages") + " pages");
            } else {
                System.out.println("No publications found on the floor " + floor);
            }
        }
        
        String LongestPublicationsql = "SELECT BI.publication_title, BI.number_of_pages " +
             "FROM " + TABLE_BOOK_INFO + " BI " +
             "INNER JOIN " + TABLE_BOOK_LOCATION + " BL ON BI.id = BL.id " +
             "WHERE BL.floor = ? " +
             "ORDER BY BI.number_of_pages DESC FETCH FIRST 1 ROWS ONLY";
        
        try (PreparedStatement statement = connection.prepareStatement(LongestPublicationsql)) {
            statement.setInt(1, floor);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                System.out.println("\nLongest publication on the floor " + floor + ":");
                System.out.println(resultSet.getString("publication_title") + " consists of " + resultSet.getInt("number_of_pages") + " pages");
            } else {
                System.out.println("No publications found on the floor " + floor);
            }
        }
    }
    //View all shelves in lexicographic order.
    private static void viewAllShelves(Connection connection) throws SQLException {
        String sql = "SELECT DISTINCT floor, shelf FROM " + TABLE_BOOK_LOCATION + " ORDER BY floor, shelf";
        try (Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(sql)) {
            System.out.println("\nAll shelves in lexicographical order:");
            System.out.printf("| %-5s | %-5s |\n",
                        "Floor", "Shelf");
            System.out.println("|-------|-------|");
            while (resultSet.next()) {
                System.out.printf("| %-5d | %-5d |\n",
                resultSet.getInt("floor"),
                resultSet.getInt("shelf"));
            }
        }
    }
}