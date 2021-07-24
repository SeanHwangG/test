// Full source : https://github.com/satansdeer/mobx-react
import React from "react";
import { NewNoteForm } from "./NewNoteForm";
import { useNotesStore } from "./NotesContext";
import { useObserver } from "mobx-react";

function App() {
  const notesStore = useNotesStore();

  return useObserver(() => (
    <>
      <ul>
        {notesStore.notes.map((note) => (
          <li onClick={
            () => notesStore.removeNote(note.id)
          } key={note.id}>{note.text}</li>
        ))}
      </ul>
      <NewNoteForm />
    </>
  ));
}

export default App;
