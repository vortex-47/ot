import QtQml 2.0
import QtQuick.LocalStorage 2.0

QtObject {
    property var db;

    function createNotesTable() {
        db.transaction(
            function (tx) {
                tx.executeSql("CREATE TABLE IF NOT EXISTS notes
                              (id INTEGER PRIMARY KEY AUTOINCREMENT,
                              date TEXT NOT NULL, notetext TEXT NOT NULL);");
            }
        );
    }
    function readAllNotes() {
        noteModel.clear();
        db.readTransaction(
            function (tx) {
                var results = tx.executeSql(
                            'SELECT id, date, notetext FROM notes order by id')
                for (var i = 0; i < results.rows.length; i++) {
                    noteModel.append({
                                         id: results.rows.item(i).id,
                                         date: results.rows.item(i).date,
                                         note: results.rows.item(i).notetext
                                     })
                }
            }
        );
    }
    function insertNote(date, note) {
        try {
            db.transaction(
                function (tx) {
                    tx.executeSql("INSERT INTO notes (date, notetext) VALUES(?, ?);", [date, note]);
                }
            );
        } catch (err) {
            console.log("Error insert note: " + err)
            return false;
        };
        readAllNotes();
        return true;
    }
    function updateNote(id, date, note) {
        try {
            db.transaction(
                function (tx) {
                    tx.executeSql("UPDATE notes SET date = ?, notetext = ? WHERE id = ?;", [date, note, id]);
                }
            );
        } catch (err) {
            console.log("Error update note: " + err)
            return false;
        };
        mainDate = ""
        mainNote = ""
        readAllNotes();
        return true;
    }
    function deleteNote(id) {
        try {
            db.transaction(
                function (tx) {
                    tx.executeSql("DELETE FROM notes WHERE id = ?;", [id]);
                }
            );
        } catch (err) {
            console.log("Error delete note: " + err)
            return false;
        };
        readAllNotes();
        return true;
    }

    Component.onCompleted: {
        db = LocalStorage.openDatabaseSync("notes", "1.0");
        createNotesTable();
    }
}
