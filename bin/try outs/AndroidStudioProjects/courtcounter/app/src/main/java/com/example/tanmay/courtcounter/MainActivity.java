package com.example.tanmay.courtcounter;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    int teama=0,teamb=0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public void addOne_a(View view)
    {
        teama++;
        displayForTeamA(teama);
    }
    public void addTwo_a(View view)
    {
        teama=teama+2;
        displayForTeamA(teama);
    }
    public void addThree_a(View view)
    {
        teama=teama+3;
        displayForTeamA(teama);
    }
    public void addOne_b(View view)
    {
        teamb++;
        displayForTeamB(teamb);
    }
    public void addTwo_b(View view)
    {
        teamb=teamb+2;
        displayForTeamB(teamb);
    }
    public void addThree_b(View view)
    {
        teamb=teamb+3;
        displayForTeamB(teamb);
    }
    /**
     * Displays the given score for Team A.
     */
    public void displayForTeamA(int score) {
        TextView scoreView = (TextView) findViewById(R.id.teamA);
        scoreView.setText(String.valueOf(score));
    }
    /** for teamB*/
    public void displayForTeamB(int score) {
        TextView scoreView = (TextView) findViewById(R.id.teamB);
        scoreView.setText(String.valueOf(score));
    }
    public void reset(View view)
    {
        teama=0;
        teamb=0;
        displayForTeamA(teama);
        displayForTeamB(teamb);
    }
}
