import firebase from "firebase/app";
import "firebase/firestore";
import "firebase/auth";
import "firebase/storage";

const config = {
  apiKey: "AIzaSyC98sPjNQHieYs2NmsJORADRDWG85U1-Z8",
  authDomain: "polar-gasket-172700.firebaseapp.com",
  databaseURL: "https://polar-gasket-172700.firebaseio.com",
  projectId: "polar-gasket-172700",
  storageBucket: "polar-gasket-172700.appspot.com",
  messagingSenderId: "536210809093",
  appId: "1:536210809093:web:cb2c0f99edf24530"
};
export const provider = new firebase.auth.GoogleAuthProvider();

export default firebase.initializeApp(config);
export const firestore = firebase.firestore();
export const auth = firebase.auth();
export const storage = firebase.storage();

export const getTodos = () =>
  firestore
    .collection("todos")
    .get()
    .then(snapshot =>
      snapshot.docs.map(doc => ({ id: doc.id, ...doc.data() }))
    );

export const listenTodos = async () => {
  await firestore.collection("todos").onSnapshot(snapshot => {
    return snapshot.docs.map(doc => ({ id: doc.id, ...doc.data() }));
  });
};

export const addTodos = todo => {
  firestore.collection("todos").add(todo);
};

export const deleteTodos = async id => {
  firestore.doc(`todos/${id}`).delete();
};
