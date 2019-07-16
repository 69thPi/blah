package com.example.tanmay.justjava;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    int quantity = 0;
    int total_price = 0;
    boolean chocolate = false;
    boolean whippedCream = false;
    public void increment(View view){
        quantity++;
        if(quantity >100)
          quantity=0;
        display(quantity);
    }
    public void decrement(View view){
        quantity--;
        if(quantity<0)
           quantity=100;
        display(quantity);
    }
    public int whipped_cream()
    {
        CheckBox b1 = (CheckBox) findViewById(R.id.crm);
        if(b1.isChecked())
            return 1;
        else
            return 0;
    }
    public int  chocolate()
    {
        CheckBox b2 = (CheckBox) findViewById(R.id.choc);
        if(b2.isChecked())
            return 1;
        else
            return 0;
    }
    public void submitOrder(View view)
    {
        composeEmail();
    }
    public String createOrderSummary()
    {
      EditText name = (EditText)findViewById(R.id.name);
        String n = name.getText().toString();
        String choc = "",whippedCream = "";
        total_price = quantity * (5 + chocolate() + whipped_cream());
        if(chocolate()==1)
            choc="YES";
        else
            choc="NO";
        if(whipped_cream()==1)
            whippedCream="YES";
        else
            whippedCream="NO";
        String print = "-----ORDER-----\n"+"Name : " + n + "\n Quantity :" + quantity + "\nWhipped cream :" + whippedCream + "\nChocolate :" +choc + "\nPrice :" + total_price;
        return print;
    }
    public void composeEmail() {
        Intent intent = new Intent(Intent.ACTION_SENDTO);
        intent.setData(Uri.parse("mailto:")); // only email apps should handle this
        intent.putExtra(Intent.EXTRA_EMAIL, Uri.parse("abc@gmail.com"));
        intent.putExtra(Intent.EXTRA_SUBJECT, "new order");
        intent.putExtra(Intent.EXTRA_TEXT, createOrderSummary());
        if (intent.resolveActivity(getPackageManager()) != null) {
            startActivity(intent);
        }
        else
            Log.i("MainActvity.java","no email app found");
    }
    private void display(int number) {
      TextView disp = (TextView) findViewById(R.id.quantity_text_view);
        disp.setText(""+quantity);
    }
}