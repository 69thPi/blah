package com.example.tanmay.first_aid;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    public final static String EXTRA_MESSAGE = "com.mycompany.myfirstapp.MESSAGE";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public void sendMsg(View view)
    {
        ArrayList<Uri> imageUris = new ArrayList<Uri>();
        Uri imageUri1 = Uri.parse(//location)
        imageUris.add(imageUri1); // Add your image URIs here
        imageUris.add(imageUri2);
        Intent intent=getIntent();
        intent.putExtra(EXTRA_MESSAGE, R.string.fracture);
        intent.putParcelableArrayListExtra(Intent.EXTRA_STREAM, imageUris);
        intent.setType("image/*");
    }

}
