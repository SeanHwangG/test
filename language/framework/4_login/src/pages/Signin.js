import React, { useState } from "react";

export default function Signin(props) {
  const [form, setForm] = useState({
    email: "",
    password: "",
  });

  const handleChange = (e) => {
    setForm({
      ...form,
      [e.target.id]: e.target.value,
    });
  };
  return (
    <form onSubmit={() => props.signin(form)}>
      <label>Username</label>
      <input
        type="text"
        required
        id="email"
        value={form.email}
        onChange={handleChange}
      />
      <label>Password</label>
      <input
        type="text"
        required
        id="password"
        value={form.password}
        onChange={handleChange}
      />
      <button type="submit">Login</button>
    </form>
  );
}
