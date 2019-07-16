package com.example.tanmay.cookies;

        import android.os.Bundle;
        import android.support.v7.app.AppCompatActivity;
        import android.view.View;
        import android.widget.Button;
        import android.widget.ImageView;
        import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /**
     * Called when the cookie should be eaten.
     */
    int img=1;
    public void eatCookie(View view) {

        // TODO: Find a reference to the ImageView in the layout. Change the image.
        if(img==1) {
            ImageView pic = (ImageView) findViewById(R.id.android_cookie_image_view);
            pic.setImageResource(R.drawable.after_cookie);
            // TODO: Find a reference to the TextView in the layout. Change the text.
            TextView text = (TextView) findViewById(R.id.status_text_view);
            text.setText("I'm So Full.");
            Button but = (Button) findViewById(R.id.but);
            but.setText("Again");
            img=0;
        }
        else if(img==0){
            ImageView pic = (ImageView) findViewById(R.id.android_cookie_image_view);
            pic.setImageResource(R.drawable.before_cookie);
            // TODO: Find a reference to the TextView in the layout. Change the text.
            TextView text = (TextView) findViewById(R.id.status_text_view);
            text.setText("I'm Hungry.");
            Button but = (Button) findViewById(R.id.but);
            but.setText("Eat Cookie");
            img=1;
        }



    }
}