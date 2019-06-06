


/**
 * Groups tests and expected results.
 *
 * @version $Revision: 588091 $ $Date: 2007-10-24 17:17:42 -0700 (Wed, 24 Oct 2007) $
 */
 public class ResultPair {
      public String item;
      public boolean valid;

      public ResultPair(String item, boolean valid) {
         this.item = item;
         this.valid = valid;  //Weather the individual part of url is valid.
      }
   }
