const mongoose = require("mongoose");
const express = require("express");
const Schema = mongoose.Schema;
const app = express();
app.use(express.static("client"));
app.use(express.json());

const bookRecordScheme = new Schema({ returnDate: String, fullName: String, title: String, publishingOffice: String, year: Number, authors: String }, { versionKey: false });
const BookRecord = mongoose.model("BookRecord", bookRecordScheme);
async function main() {
    try {
        await mongoose.connect("mongodb://127.0.0.1:27017/librarydb");
        app.listen(3000);
        console.log("Сервер ожидает подключения...");
    }
    catch (err) {
        return console.log(err);
    }
}

app.get("/api/bookRecords", async (req, res) => {
    const bookRecords = await BookRecord.find({});
    res.send(bookRecords);
});
app.get("/api/bookRecords/:id", async (req, res) => {
    const id = req.params.id;
    const bookRecord = await BookRecord.findById(id);
    if (bookRecord) res.send(bookRecord);
    else res.sendStatus(404);
});
app.post("/api/bookRecords", async (req, res) => {
    if (!req.body) return res.sendStatus(400);
    const returnDate = req.body.returnDate;
    const fullName = req.body.fullName;
    const title = req.body.title;
    const publishingOffice = req.body.publishingOffice;
    const year = req.body.year;
    const authors = req.body.authors;
    const bookRecord = new BookRecord({ returnDate: returnDate, fullName: fullName, title: title, publishingOffice: publishingOffice, year: year, authors: authors });
    await bookRecord.save();
    res.send(bookRecord);
});
app.delete("/api/bookRecords/:id", async (req, res) => {
    const id = req.params.id;
    const bookRecord = await BookRecord.findByIdAndDelete(id);
    if (bookRecord) res.send(bookRecord);
    else res.sendStatus(404);
});
app.put("/api/bookRecords/:id", async (req, res) => {
    if (!req.body) return res.sendStatus(400);
    const id = req.params.id;
    const returnDate = req.body.returnDate;
    const fullName = req.body.fullName;
    const title = req.body.title;
    const publishingOffice = req.body.publishingOffice;
    const year = req.body.year;
    const authors = req.body.authors;
    const newBookRecord = { returnDate: returnDate, fullName: fullName, title: title, publishingOffice: publishingOffice, year: year, authors: authors };
    const bookRecord = await BookRecord.findOneAndUpdate({ _id: id }, newBookRecord, { new: true });
    if (bookRecord) res.send(bookRecord);
    else res.sendStatus(404);
});
main();
// прослушиваем прерывание работы программы (ctrl-c)
process.on("SIGINT", async () => {
    await mongoose.disconnect();
    console.log("Приложение завершило работу");
    process.exit();
});