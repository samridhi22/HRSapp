#ifndef SKILLMENU_H
#define SKILLMENU_H

/**@file SkillMenu.h
 *@brief All the menu handlers related to skill are declared.
 *
 * <BR>NAME: SkillMenu
 * 
 * <BR>BASE CLASSES: No Parent
 * 
 * <BR>PURPOSE: All the menu handlers related to skill are declared.
 * 
 *
 * <BR>AUTHOR: Arun Veeramany
 * <BR>$Revision: 9th Dec'05
 * 
 * <BR>$Log: 9th Dec'05
 * 
 * <BR>COPYRIGHT NOTICE:
 * <BR>Copyright (c) 2005 C++ Capability team at Accenture. All rights reserved.
 */


/**@namespace ui
   @brief Declares core UI classes and those that depend on them
 */

namespace ui
{
/**@class SkillMenu
  * @brief All the menu handlers related to skill are declared.
  * <BR> 
  * <PRE> 
  * Function Pointers in the MenuHandler point to these methods.
  * These are executed when the corresponding menu item is chosen.
  * </PRE> 
  */
  class SkillMenu
  {
  public:
    /**@fn create(void)
     * @brief displays the Add New Skill Form 
     * @param none
     * @return bool - whether to go back to previous menu or exit
     */   
    static bool create(void);

    /**@fn update(void)
     * @brief displays the Update Existing Skill Form 
     * @param none
     * @return bool - whether to go back to previous menu or exit
     */   
    static bool update(void);

    /**@fn search(void)
     * @brief displays the Search Skill by Id Form 
     * @param none
     * @return bool - whether to go back to previous menu or exit
     */   
    static bool search(void);

    /**@fn searchByName(void)
     * @brief displays the Search Skill by Name Form 
     * @param none
     * @return bool - whether to go back to previous menu or exit
     */   
    static bool searchByName(void);
  };
}
#endif //SKILLMENU_H
