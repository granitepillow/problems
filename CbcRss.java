package org.jbhyde;

/**
 * Parses the CBC Top Stories RSS feed and generates a list of the most recent stories, sorted by date.
 * Jameson Hyde (jameson.hyde@gmail.com)
 * January 20, 2013
 */

import java.net.*;
import java.util.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.lang.reflect.Array;
import java.lang.StringBuilder;


//CbcRss
/**
 * Class to read and parse CBC stories RSS feed
 */
public class CbcRss
{
    //RSS URL from which to retrieve stories
    private static final String RSS_URL = "http://rss.cbc.ca/lineup/topstories.xml";
    //Format of publication date on each story at RSS site.
    private static final String DATE_FORMAT = "EEE, dd MMM yyyy HH:mm:ss ZZZ";
    public Story[] stories;

    //Story
    /**
     * Class defining a news story
     */
    public class Story
    {
        public String title;
        public String link;
        public Date date;

        //Equals()
        /**
         * Compare an object with this instance and determine if they are the same.
         * @param obj Object to be compared with this instance.
         * @return true if this instance and obj are the same story, false otherwise.
         */
        public boolean Equals(Object obj)
        {
            //confirm first if obj is an instance of Story
            if(obj instanceof Story) {
                return this.Equals((Story)obj);
            } else {
                return false;
            }
        }

        //Equals()
        /**
         * Compare a story with this instance and determine if they are the same.
         * @param story Story to be compared with this instance.
         * @return true if this instance and story are the same story, false otherwise.
         */
        public boolean Equals(Story story)
        {
            return this.link == story.link;
        }
    }
    
    //StoryComparer
    /**
     * Private class to compare stories.
     */
    private static class StoryComparer implements Comparator<Story> {
    
        //compare()
        /**
         * Compare two stories and return a value indicating which is more recent.
         * @param x One story to be compared.
         * @param y A second story to be compared.
         * @return An integer: < 0 if x is older than y, > 0 if y is older than x, or 0 if they are the same.
         */
        public int compare(Story x, Story y)
        {
            //null checking to push all null Stories to the oldest
            if(null ==x || null == y) {
                if(null == x && null == y) {
                    return 0;
                } else if(null == x) {
                    return -1;
                } else {
                    return 1;
                }
            }
            if(x.Equals(y)) {
                return 0;
            }
            else {
                return x.date.compareTo(y.date);
            }
        }
    }

    //getContent()
    /**
     * Read XML content from RSS site and return the retrieved string.
     */
    private static String getContent()
    {
        URL url;
        HttpURLConnection conn;
        BufferedReader rd;
        String line;
        StringBuilder builder = new StringBuilder();
        
        try {
            url = new URL(RSS_URL);
            conn =(HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
            rd = new BufferedReader(new InputStreamReader(conn.getInputStream()));

            //read and append lines to buffer until end of stream
            while((line = rd.readLine()) != null) {
                builder.append(line);
            }
        }
        catch(Exception e) {
            throw new RuntimeException(e);
        }
        return builder.toString();
    }

    //fetchAndParse()
    /**
     * Fetch XML data and parse stories from it.
     * @return A list of stories parsed from the content.
     */
    private Story[] fetchAndParse()
    {
        ArrayList<String> items = new ArrayList<String>();
        SimpleDateFormat formatter = new SimpleDateFormat(DATE_FORMAT);
        String content;
        int start = 0;
        
        //fetch XML data
        content = getContent();
        
        //parse news items from XML data until end of content
        while(items.size() < Integer.MAX_VALUE) {
            int nextItemStart = content.indexOf("<item", start);
            int nextItemEnd = content.indexOf("</item>", nextItemStart);
            if(nextItemStart < 0 || nextItemEnd < 0) {
                break;
            }

            String nextItem = content.substring(nextItemStart, nextItemEnd);
            items.add(nextItem);

            start = nextItemEnd;
        }

        //from parsed items create a list of stories and parse each story property from the items
        Story storyList[] = new Story[items.size()];
        for(int i = 0; i < items.size() ; i++)
        {
            Story story = new Story();
            String dateStr = items.get(i).replaceAll(".*<pubDate>", "").replaceAll("</pubDate>.*", "");

            story.title = items.get(i).replaceAll(".*<title>", "").replaceAll("</title>.*", "");
            story.title = story.title.replaceAll(".*<!\\[CDATA\\[", "").replaceAll("\\]\\]>.*", "");
            story.link = items.get(i).replaceAll(".*<link>", "").replaceAll("</link>.*", "");
            try {
                story.date = formatter.parse(dateStr);
            } catch(ParseException pe) {
                System.out.println("Cannot parse \"" + dateStr + "\"");
                continue;
            }

            storyList[i] = story;
        }
        return storyList;
    }

    //GetMostRecentN()
    /**
     * Return the N most recent elements given a list of elements.  
     * Note that this was designed for news stories, which are sorted chronologically, but other classes can be provided and sorted by an alternate property.
     * @param N The number of most recent elements to return, if N is 0, all elements from the list will be returned in order.
     * @return An array of the N most recent elements.
     */
    private static <T> T[] GetMostRecentN(T[] elements, Comparator comparer, int N, Class<? extends T> cls)
    {
        if(N > elements.length || N <= 0) {
            N = elements.length;
        }

        List<T> listElements = Arrays.asList(Arrays.copyOf(elements, elements.length));

        //sort the elements
        Collections.sort(listElements, comparer);

        //in the case of sorting stories, the array will be in chronological order, so to get the most recent ones, 
        //we will append stories from the end of the array to a new recent elements array
        T[] recentElementsArray =(T[])Array.newInstance(cls, N);
        for(int i = 0; i < N; i++) {
            recentElementsArray[i] = listElements.get(listElements.size() - i - 1);
        }

        return recentElementsArray;

    }
    
    //GetStories()
    /**
     * Grab the latest content from the CBC RSS feed, parse the stories and provide a list of the most recent N stories.
     * @param N The number of most recent stories to return, if N is 0, all stories from the RSS feed will be returned in reverse-chronological order.
     * @return An array of the N most recent stories.
     */
    public Story[] GetStories(int N)
    {
        stories = fetchAndParse();
        if(0 == stories.length) {
            return null;
        }
        return GetMostRecentN(stories, new StoryComparer(), N, stories[0].getClass());

    }
}
