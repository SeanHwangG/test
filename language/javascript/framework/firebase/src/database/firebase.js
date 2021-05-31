import firebaseApp from "firebase/app";
import "firebase/auth";
import "firebase/firestore";

const firebase = firebaseApp.initializeApp({
  apiKey: "AIzaSyC98sPjNQHieYs2NmsJORADRDWG85U1-Z8",
  authDomain: "polar-gasket-172700.firebaseapp.com",
  databaseURL: "https://polar-gasket-172700.firebaseio.com",
  projectId: "polar-gasket-172700",
  storageBucket: "polar-gasket-172700.appspot.com",
  messagingSenderId: "536210809093",
  appId: "1:536210809093:web:cb2c0f99edf24530"
});

window.firebase = firebaseApp;

export const auth = firebaseApp.auth();
export const firestore = firebaseApp.firestore();
export default firebase;
